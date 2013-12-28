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
            Utilities::requireException(dValues_.size() == dVariables_.size(), "Variables and values are not the same size","InterExtrapolation1D::InterExtrapolation1D");
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
                    dSecondDerivativeValues_.at(1) = u.at(1) = 0.0;
                }
                else 
                { 
                    //or else to have a specified first derivative.
                    dSecondDerivativeValues_.at(1) = -0.5;
                    u.at(1)=(3.0/(dVariables_.at(2)-dVariables_.at(1)))*((dValues_.at(2)-dValues_.at(1))/(dVariables_.at(2)-dVariables_.at(1))-yp1);
                }
                
                for (i=2;i<=n-1;i++) 
                { 
                    //This is the decomposition loop of the tridiagonal algorithm.
                    //y2 and u are used for temporary storage of the decomposed factors.
                    sig=(dVariables_.at(i)-dVariables_.at(i-1))/(dVariables_.at(i+1)-dVariables_.at(i-1)); // bit weird no ?!
                    p=sig*dSecondDerivativeValues_.at(i-1)+2.0;
                    dSecondDerivativeValues_.at(i)=(sig-1.0)/p;
                    u.at(i)=(dValues_.at(i+1)-dValues_.at(i))/(dVariables_.at(i+1)-dVariables_.at(i)) - (dValues_.at(i)-dValues_.at(i-1))/(dVariables_.at(i)-dVariables_.at(i-1));
                    u.at(i)=(6.0*u.at(i)/(dVariables_.at(i+1)-dVariables_.at(i-1))-sig*u.at(i-1))/p;
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
                    un=(3.0/(dVariables_.at(n)-dVariables_.at(n-1)))*(ypn-(dValues_.at(n)-dValues_.at(n-1))/(dVariables_.at(n)-dVariables_.at(n-1)));
                }
                dSecondDerivativeValues_.at(n)=(un-qn*u.at(n-1))/(qn*dSecondDerivativeValues_.at(n-1)+1.0);
                //Set second derivative at edge to 0.0
                dSecondDerivativeValues_.at(n) = 0.0;
                
                //This is the backsubstitution loop of the tridiagonal algorithm
                for (k=n-1;k>=1;k--) 
                {
                    dSecondDerivativeValues_.at(k)=dSecondDerivativeValues_.at(k)*dSecondDerivativeValues_.at(k+1)+u.at(k);
                }
                
                //  Set second derivative at edge to 0
                //dSecondDerivativeValues_[1] = 0.0;

                //  Free u
                u.clear();
            }
        }
        
        double InterExtrapolation1D::operator()(double dVariable) const
        {
            //  NEAR Extrapolation
            if (dVariable < dVariables_.front())
            {
                return dValues_.front();
            }
            else if (dVariable > dVariables_.back())
            {
                return dValues_.back();
            }
			if (eInterpolationType_ == LIN)
            {
				// BEGINNING OF LINEAR CASE
				double dResult = 0.0 ;
				std::size_t iUpperIndex = 0, iLowerIndex = 0;
				bool bUpper = false, bLower = false ;
				
				for (std::size_t iRunningIndex = 0; iRunningIndex < dVariables_.size(); ++iRunningIndex)
                {
					double dRunningVariable = dVariables_.at(iRunningIndex) ;
					if (dRunningVariable > dVariable)
                    {
						if (bUpper)
                        {
							if (dRunningVariable < dVariables_.at(iUpperIndex))
                            {
								iUpperIndex = iRunningIndex ;
							}
						}
						else
                        {
							bUpper = true ;
							iUpperIndex = iRunningIndex ;
						}
						if (!bLower && dRunningVariable > dVariables_.at(iLowerIndex))
                        {
							iLowerIndex = iRunningIndex ;
						}
					}
					if (dRunningVariable <= dVariable)
                    {
						if (bLower)
                        {
							if (dRunningVariable > dVariables_.at(iLowerIndex))
                            {
								iLowerIndex = iRunningIndex ;
							}
						}
						else
                        {
							bLower = true ;
							iLowerIndex = iRunningIndex ;
						}
						if (!bUpper && dRunningVariable <= dVariables_.at(iUpperIndex))
                        {
							iUpperIndex = iRunningIndex ;
						}
					}
				}
				
				if (dVariables_.at(iUpperIndex) == dVariables_.at(iLowerIndex))
                {
					return dValues_.at(iUpperIndex);
				}
				else
                {
					dResult = dValues_.at(iLowerIndex) + (dValues_.at(iUpperIndex) - dValues_.at(iLowerIndex)) * (dVariable - dVariables_.at(iLowerIndex)) / (dVariables_.at(iUpperIndex) - dVariables_.at(iLowerIndex)) ;
					return dResult ;
				}
			}
			// END OF LINEAR CASE
			else
            {
				
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
                    if (dVariable > dVariables_.at(iNValues_ - 1))
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
                
                if (eInterpolationType_ != LIN && eInterpolationType_ != SPLINE_CUBIC && eInterpolationType_ != RAW && eInterpolationType_ != HERMITE_SPLINE_CUBIC)
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
                        dResult = dValues_.at(iValue1) + (dValues_.at(iValue2) - dValues_.at(iValue1)) / (dVariables_.at(iValue2) - dVariables_.at(iValue1)) * (dVariable - dVariables_.at(iValue1));
                        break;
                    }
                    case NEAR:
                    {
                        dResult = iValue2 == (int)iNValues_ || iValue2 == 0 ? dValues_.at(iValue2) : std::abs(dVariable - dVariables_.at(iValue1)) < std::abs(dVariable - dVariables_.at(iValue2)) ? dValues_.at(iValue1) : dValues_.at(iValue2);
                        break;
                    }
                    case RIGHT_CONTINUOUS:
                    {
                        dResult = iValue2 == (int)iNValues_? dValues_.at(iValue2 - 1) : dValues_.at(iValue2);
                        break;
                    }
                    case LEFT_CONTINUOUS:
                    {
                        dResult = iValue1 == -1 ? dValues_.at(0) : dValues_.at(iValue1);
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
                            if (dVariables_.at(k) > dVariable)
                                khi=k;
                            else 
                                klo=k;
                        }
                        //klo and khi now bracket the input value of x.
                        //khi = iValue2
                        //  klo = iValue1
                        h=dVariables_.at(khi)-dVariables_.at(klo);
                        //  The variables must be distinct
                        
                        a=(dVariables_.at(khi)-dVariable)/h;
                        b=(dVariable-dVariables_.at(klo))/h;
                        //Cubic spline polynomial is now evaluated.
                        if (dVariable < dVariables_.back())
                        {
                            dResult=a*dValues_.at(klo)+b*dValues_.at(khi)+((a*a*a-a)*dSecondDerivativeValues_.at(klo)+(b*b*b-b)*dSecondDerivativeValues_.at(khi))*(h*h)/6.0;
                        }
                        else
                        {
                            std::size_t n = dVariables_.size();
                            dResult = dValues_.back() + (dVariable - dVariables_.back()) * (-(dValues_.at(n - 1) - dValues_.at(n - 2))/(dVariables_.at(n - 1) - dVariables_.at(n - 2)) + (dSecondDerivativeValues_.at(n - 2)) /(6.0 * (dVariables_.at(n - 1) - dVariables_.at(n - 2))) + (dSecondDerivativeValues_.at(n - 1)) /(3.0 * (dVariables_.at(n - 1) - dVariables_.at(n - 2))));
                        }
                        break;
                    }
                    case RAW:
                    {
                        //  raw interpolation as described in http://www.math.ku.dk/~rolf/HaganWest.pdf by Hagan and West.
                        //  Linear interpolation in the log of the discount factors
#ifndef EPSILON_RAW
#define EPSILON_RAW 1e-07
#endif
                        Utilities::requireException(fabs(dVariable) > EPSILON_RAW, "Cannot perform Raw interpolation, variable is too small","InterExtrapolation1D::Interp1D");
                        dResult = 1.0 / dVariable * ((dVariable - dVariables_.at(iValue1)) / (dVariables_.at(iValue2) - dVariables_.at(iValue1)) * dValues_.at(iValue2) * dVariables_.at(iValue2) + (dVariables_.at(iValue2) - dVariable) / (dVariables_.at(iValue2) - dVariables_.at(iValue1)) * dValues_.at(iValue1) * dVariables_.at(iValue1) );
                        break;
                    }
                    case HERMITE_SPLINE_CUBIC:
                    {
                        double dm_1 = 0.0, dm_2 = 0.0;
                        if (iValue2 == iNValues_ - 1)
                        {
                            dm_1 = (dValues_.back() - dValues_.at(iNValues_ - 2)) / (dVariables_.back() - dVariables_.at(iNValues_ - 2));
                        }
                        else if (iValue1 == 0)
                        {
                            dm_2 = (dValues_.at(1) - dValues_.at(0)) / (dVariables_.at(1) - dVariables_.at(0));
                        }
                        else
                        {
                            dm_1 = (dValues_.at(iValue1 + 1) - dValues_.at(iValue1)) / (dVariables_.at(iValue1 + 1) - dVariables_.at(iValue1));
                            dm_2 = (dValues_.at(iValue2 + 1) - dValues_.at(iValue2)) / (dVariables_.at(iValue2 + 1) - dVariables_.at(iValue2));
                        }
                        
                        double t = (dVariable - dVariables_.at(iValue1)) / (dVariables_.at(iValue2) - dVariables_.at(iValue1));
                        
                        return (2 * t * t * t - 3 * t * t + 1) * dValues_.at(iValue1) + (t * t * t - 2 * t * t + t) * dm_1 * (dVariables_.at(iValue2) - dVariables_.at(iValue1)) + (-2. * t * t * t + 3. * t * t) * dValues_.at(iValue2) + (t * t * t - t * t) * dm_2 * (dVariables_.at(iValue2) - dVariables_.at(iValue1));
                        break;
                    }
                        
                    default:
                        break;
                }
                
                
                return dResult;
			}
        }
        
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
                Result[iter->first] = sInterp1D(dValue.find(iter->first)->second);
            }
            return Result;
        }

    }
}