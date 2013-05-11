//
//  InterExtrapolation.cpp
//  Seminaire
//
//  Created by Alexandre HUMEAU on 10/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "InterExtrapolation.h"
#include "VectorUtilities.h"
#include <cmath>
#include "Require.h"

namespace Utilities
{
    namespace Interp 
    {
        InterExtrapolation1D::InterExtrapolation1D() : eInterpolationType_(NEAR), iNValues_(0)
        {}
        
        InterExtrapolation1D::InterExtrapolation1D(const std::vector<double> & dVariables,
                                                   const std::vector<double> & dValues,
                                                   InterExtrapolationType eInterpolationType) : 
        
        iNValues_(dValues.size()),
        dValues_(dValues),
        dVariables_(dVariables),
        eInterpolationType_(eInterpolationType)
        
        {
            Utilities::require(dValues_.size() == dVariables_.size(), "Values and variables are not of the same size");
            if (eInterpolationType_ == SPLINE_CUBIC)
            {
                //  Compute the second derivative
                
                //  Adapted from Numerical Recipes in C (page 139)
                
                //Given arrays x[1..n] and y[1..n] containing a tabulated function, i.e., yi = f(xi), with
                //x1 < x2 < .. . < xN, and given values yp1 and ypn for the first derivative of the interpolating
                //    function at points 1 and n, respectively, this routine returns an array y2[1..n] that contains
                //    the second derivatives of the interpolating function at the tabulated points xi. If yp1 and/or
                //    ypn are equal to 1 × 1030 or larger, the routine is signaled to set the corresponding boundary
                //    condition for a natural spline, with zero second derivative on that boundary.
                
                double yp1 = 0.0, ypn = 0.0;
                int i,k, n = static_cast<int>(dVariables_.size());
                double p,qn,sig,un;
                std::vector<double> u(n-1);
                //  Had to resize the second derivative values to n+1 because it was coded this way in Numerical Recipes (to be changed)
                dSecondDerivativeValues_.resize(n+1);
                if (yp1 > 0.99e30)
                {
                    //The lower boundary condition is set either to be "natural"
                    dSecondDerivativeValues_[1] = u[1] = 0.0;
                }
                else 
                { 
                    //or else to have a specified first derivative.
                    dSecondDerivativeValues_[1] = -0.5;
                    u[1]=(3.0/(dVariables_[2]-dVariables_[1]))*((dValues_[2]-dValues_[1])/(dVariables_[2]-dVariables_[1])-yp1);
                }
                
                for (i=2;i<=n-1;i++) 
                { 
                    //This is the decomposition loop of the tridiagonal algorithm.
                    //y2 and u are used for temporary storage of the decomposed factors.
                    sig=(dVariables_[i]-dVariables_[i-1])/(dVariables_[i+1]-dVariables_[i-1]);
                    p=sig*dSecondDerivativeValues_[i-1]+2.0;
                    dSecondDerivativeValues_[i]=(sig-1.0)/p;
                    u[i]=(dValues_[i+1]-dValues_[i])/(dVariables_[i+1]-dVariables_[i]) - (dValues_[i]-dValues_[i-1])/(dVariables_[i]-dVariables_[i-1]);
                    u[i]=(6.0*u[i]/(dVariables_[i+1]-dVariables_[i-1])-sig*u[i-1])/p;
                }
                
                if (ypn > 0.99e30) 
                {
                    //The upper boundary condition is set either to be natural 
                    qn=un=0.0;
                }
                else 
                { 
                    //or else to have a specified first derivative.
                    qn=0.5;
                    un=(3.0/(dVariables_[n]-dVariables_[n-1]))*(ypn-(dValues_[n]-dValues_[n-1])/(dVariables_[n]-dVariables_[n-1]));
                }
                dSecondDerivativeValues_[n]=(un-qn*u[n-1])/(qn*dSecondDerivativeValues_[n-1]+1.0);
                //Set second derivative at edge to 0.0
                dSecondDerivativeValues_[n] = 0.0;
                
                //This is the backsubstitution loop of the tridiagonal algorithm
                for (k=n-1;k>=1;k--) 
                {
                    dSecondDerivativeValues_[k]=dSecondDerivativeValues_[k]*dSecondDerivativeValues_[k+1]+u[k]; 
                }
                
                //  Set second derivative at edge to 0
                //dSecondDerivativeValues_[1] = 0.0;

                //  Free u
                u.clear();
            }
        }
        
        InterExtrapolation1D::~InterExtrapolation1D()
        {}
        
        double InterExtrapolation1D::Interp1D(double dVariable) const
        {
			if (eInterpolationType_ == LIN) {
				// BEGINNING OF LINEAR CASE
				double dResult = 0.0 ;
				std::size_t iUpperIndex = 0, iLowerIndex = 0;
				bool bUpper = false, bLower = false ;
				
				for (std::size_t iRunningIndex = 0; iRunningIndex < dVariables_.size(); ++iRunningIndex) {
					double dRunningVariable = dVariables_[iRunningIndex] ;
					if (dRunningVariable > dVariable) {
						if (bUpper) {
							if (dRunningVariable < dVariables_[iUpperIndex]) {
								iUpperIndex = iRunningIndex ;
							}
						}
						else {
							bUpper = true ;
							iUpperIndex = iRunningIndex ;
						}
						if (!bLower && dRunningVariable > dVariables_[iLowerIndex]) {
							iLowerIndex = iRunningIndex ;
						}
					}
					if (dRunningVariable <= dVariable) {
						if (bLower) {
							if (dRunningVariable > dVariables_[iLowerIndex]) {
								iLowerIndex = iRunningIndex ;
							}
						}
						else {
							bLower = true ;
							iLowerIndex = iRunningIndex ;
						}
						if (!bUpper && dRunningVariable <= dVariables_[iUpperIndex]) {
							iUpperIndex = iRunningIndex ;
						}
					}
				}
				
				if (dVariables_[iUpperIndex] == dVariables_[iLowerIndex]) {
					return dValues_[iUpperIndex] ;
				}
				else {
					dResult = dValues_[iLowerIndex] + (dValues_[iUpperIndex] - dValues_[iLowerIndex]) * (dVariable - dVariables_[iLowerIndex]) / (dVariables_[iUpperIndex] - dVariables_[iLowerIndex]) ;
					return dResult ;
				}
			}
			// END OF LINEAR CASE
			else {
				
                double dResult = 0.0;
                int iValue, iValue1, iValue2;
                
                // if the variable hasn't been found, iValue=exc value
                if (!IsFound(dVariables_, dVariable, (std::size_t*)&iValue))
                {
                    iValue = Utilities::FindInVector(dVariables_, dVariable);
                }
                //iValue = 1;
                iValue1 = iValue;
                iValue2 = iValue + 1;
                
                if (iValue == -1)
                {
                    // Extrapolation
                    if (dVariable > dVariables_[iNValues_ - 1])
                    {
                        iValue1 = static_cast<int>(iNValues_ - 2);
                        iValue2 = static_cast<int>(iNValues_ - 1);
                    }
                    else
                    {
                        // dVariable < dVariables[0]
                        iValue1 = 0;
                        iValue2 = 1;
                    }
                }
                
                if (eInterpolationType_ != LIN && eInterpolationType_ != SPLINE_CUBIC)
                {
                    //  Adapts the iValue for RIGHT_CONTINUOUS and LEFT_CONTINUOUS interpolation types
                    if (iValue == -1)
                    {
                        if (iValue2 == static_cast<int>(iNValues_ - 1))
                        {
                            iValue2++;
                            iValue1++;
                        }
                        else
                        {
                            iValue2--;
                            iValue1--;
                        }
                    }
                }
                
                switch (eInterpolationType_)
                {
                    case LIN:
                    {
                        dResult = dValues_[iValue1] + (dValues_[iValue2] - dValues_[iValue1]) / (dVariables_[iValue2] - dVariables_[iValue1]) * (dVariable - dVariables_[iValue1]);
                        break;
                    }
                    case NEAR:
                    {
                        dResult = iValue2 == (int)iNValues_ || iValue2 == 0 ? dValues_[iValue2] : std::abs(dVariable - dVariables_[iValue1]) < std::abs(dVariable - dVariables_[iValue2]) ? dValues_[iValue1] : dValues_[iValue2];
                        break;
                    }
                    case RIGHT_CONTINUOUS:
                    {
                        dResult = iValue2 == (int)iNValues_? dValues_[iValue2 - 1] : dValues_[iValue2];
                        break;
                    }
                    case LEFT_CONTINUOUS:
                    {
                        dResult = iValue1 == -1 ? dValues_[0] : dValues_[iValue1];
                        break;
                    }
                    case SPLINE_CUBIC:
                    {
                        //Given the arrays xa[1..n] and ya[1..n], which tabulate a function (with the xai’s in order),
                        //and given the array y2a[1..n], which is the output from spline above, and given a value of
                        //x, this routine returns a cubic-spline interpolated value y.
                        //{
                        int klo,khi,k;
                        float h,b,a;
                        klo=1;
                        //We will find the right place in the table by means of
                        //bisection. This is optimal if sequential calls to this
                        //    routine are at random values of x. If sequential calls
                        //    are in order, and closely spaced, one would do better
                        //        to store previous values of klo and khi and test if
                        //            they remain appropriate on the next call.
                        khi=static_cast<int>(dValues_.size());
                        while (khi-klo > 1) 
                        {
                            k=(khi+klo) >> 1;
                            if (dVariables_[k] > dVariable)
                                khi=k;
                            else 
                                klo=k;
                        }
                        //klo and khi now bracket the input value of x.
                        //khi = iValue2
                        //  klo = iValue1
                        h=dVariables_[khi]-dVariables_[klo];
                        //  The variables must be distinct
                        
                        a=(dVariables_[khi]-dVariable)/h;
                        b=(dVariable-dVariables_[klo])/h; 
                        //Cubic spline polynomial is now evaluated.
                        if (dVariable < dVariables_.back())
                        {
                            dResult=a*dValues_[klo]+b*dValues_[khi]+((a*a*a-a)*dSecondDerivativeValues_[klo]+(b*b*b-b)*dSecondDerivativeValues_[khi])*(h*h)/6.0;
                        }
                        else
                        {
                            std::size_t n = dVariables_.size();
                            dResult = dValues_.back() + (dVariable - dVariables_.back()) * (-(dValues_[n - 1] - dValues_[n - 2])/(dVariables_[n - 1] - dVariables_[n - 2]) + (dSecondDerivativeValues_[n - 2]) /(6.0 * (dVariables_[n - 1] - dVariables_[n - 2])) + (dSecondDerivativeValues_[n - 1]) /(3.0 * (dVariables_[n - 1] - dVariables_[n - 2])));
                        }
                        break;
                    }
                        
                    default:
                        break;
                }
                
                
                return dResult;
			}
        }
        
        InterExtrapolationnD::InterExtrapolationnD()
        {}
        
        InterExtrapolationnD::InterExtrapolationnD(const std::map<std::size_t, std::vector<double> > & dVariables,
                                                   const std::map<std::size_t, std::vector<double> > & dValues,
                                                   InterExtrapolationType eInterpolationType)
        : dVariables_(dVariables), dValues_(dValues), eInterpolationType_(eInterpolationType)
        {}
        
        std::map<std::size_t, double> InterExtrapolationnD::InterpnD(const std::map<size_t, double> &dValue)
        {
            std::map<std::size_t, double> Result;
            std::map<std::size_t, std::vector<double> >::iterator iter;
            for (iter = dVariables_.begin() ; iter != dVariables_.end() ; ++iter)
            {
                InterExtrapolation1D sInterp1D(iter->second, dVariables_.find(iter->first)->second, eInterpolationType_);
                Result[iter->first] = sInterp1D.Interp1D(dValue.find(iter->first)->second);
            }
            return Result;
        }

    }
}