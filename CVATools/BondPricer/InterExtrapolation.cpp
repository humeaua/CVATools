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
#include "Exception.h"

namespace Utilities
{
    namespace Interp 
    {
        Interpolator::Interpolator(const std::vector<double> & dVariables, const std::vector<double> & dValues) : dVariables_(dVariables), dValues_(dValues)
        {
            REQUIREEXCEPTION(dValues_.size() == dVariables_.size(), "Values and Variables are not the same size");
        }
        
        void Interpolator::FindIndex(double dVariable, int & iValue1) const
        {
            int iValue = 0;
            std::size_t iNValues = dValues_.size();
            
            // if the variable is not in the variable vector, we find the index s.t. variables[index] < variable <= variables[index + 1]
            if (!IsFound(dVariables_, dVariable, iValue))
            {
                iValue1 = Utilities::FindInVector(dVariables_, dVariable);
            }
            else
            {
                iValue1 = static_cast<int>(iValue);
            }
            
            if (dVariable < dVariables_.front())
            {
                iValue1 = 0;
            }
            else if (dVariable > dVariables_.back())
            {
                iValue1 = static_cast<int>(iNValues - 2);
            }
        }
        
        double Interpolator::ValueIfVariablePresent(int iVar) const
        {
            std::size_t lVar = static_cast<size_t>(iVar);
            return dValues_.at(lVar);
        }
        
        size_t Interpolator::size() const
        {
            return dVariables_.size();
        }
        
        LinearInterpolator::LinearInterpolator(const std::vector<double> & dVariables, const std::vector<double> & dValues) : Interpolator(dVariables, dValues)
        {}
        
        double LinearInterpolator::operator()(double dVariable) const
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
        
        LogLinDFInterpolator::LogLinDFInterpolator(const std::vector<double> & dVariables, const std::vector<double> & dValues) : Interpolator(dVariables, dValues), m_epsilon(1e-07)
        {}

        double LogLinDFInterpolator::operator()(double dVariable) const
        {
            int iValue1 = 0, iValue2 = 0;
            FindIndex(dVariable, iValue1);
            if (iValue1 == dVariables_.size() - 1)
            {
                iValue2 = iValue1--;
            }
            else
            {
                iValue2 = iValue1 + 1;
            }
            //  raw interpolation as described in http://www.math.ku.dk/~rolf/HaganWest.pdf by Hagan and West.
            //  Linear interpolation in the log of the discount factors

            //REQUIREEXCEPTION(fabs(dVariable) > m_epsilon, "Cannot perform Raw interpolation, variable is too small");
            if (std::abs(dVariable) < m_epsilon)
            {
                throw EXCEPTION("Cannot perform Raw interpolation, variable is too small");
            }
            return 1.0 / dVariable * ((dVariable - dVariables_.at(iValue1)) / (dVariables_.at(iValue2) - dVariables_.at(iValue1)) * dValues_.at(iValue2) * dVariables_.at(iValue2) + (dVariables_.at(iValue2) - dVariable) / (dVariables_.at(iValue2) - dVariables_.at(iValue1)) * dValues_.at(iValue1) * dVariables_.at(iValue1) );
        }
        
        NearInterpolator::NearInterpolator(const std::vector<double> & dVariables, const std::vector<double> & dValues) : Interpolator(dVariables, dValues)
        {}
        
        double NearInterpolator::operator()(double dVariable) const
        {
            int iValue1 = 0;
            FindIndex(dVariable, iValue1);
            int iValue2 = iValue1 + 1;
            if (iValue2 == static_cast<int>(dVariables_.size()) || iValue2 == 0)
            {
                return dValues_.at(iValue2);
            }
            else if (std::abs(dVariable - dVariables_.at(iValue1)) < std::abs(dVariable - dVariables_.at(iValue2)))
            {
                return dValues_.at(iValue1);
            }
            else
            {
                return dValues_.at(iValue2);
            }
        }
        
        void NearInterpolator::FindIndex(double dVariable, int& iValue1) const
        {
            Interpolator::FindIndex(dVariable, iValue1);
            
            //  Adapts the iValue for RIGHT_CONTINUOUS and LEFT_CONTINUOUS interpolation types
            if (iValue1 == -1)
            {
                (iValue1)++;
            }
        }
        
        LeftContinuousInterpolator::LeftContinuousInterpolator(const std::vector<double> & dVariables, const std::vector<double> & dValues) : Interpolator(dVariables, dValues)
        {}
        
        double LeftContinuousInterpolator::operator()(double dVariable) const
        {
            int iValue1 = 0;
            FindIndex(dVariable, iValue1);
            if (iValue1 == static_cast<int>(dVariables_.size()))
            {
                return dValues_.back();
            }
            else
            {
                return dValues_.at(iValue1);
            }
        }
        
        void LeftContinuousInterpolator::FindIndex(double dVariable, int &iValue1) const
        {
            // if the variable is not in the variable vector, we find the index s.t. variables[index] < variable <= variables[index + 1]
            if (!IsFound(dVariables_, dVariable, iValue1))
            {
                iValue1 = Utilities::FindInVector(dVariables_, dVariable);
            }
            
            if (dVariable < dVariables_.front())
            {
                iValue1 = 0;
            }
            else
            {
                iValue1++;
            }
        }
        
        RightContinuousInterpolator::RightContinuousInterpolator(const std::vector<double> & dVariables, const std::vector<double> & dValues) : Interpolator(dVariables, dValues)
        {}
        
        double RightContinuousInterpolator::operator()(double dVariable) const
        {
            int iValue1 = 0;
            FindIndex(dVariable, iValue1);
            if (iValue1 == -1)
            {
                return dValues_.at(0);
            }
            else
            {
                return dValues_.at(iValue1);
            }
        }
        
        HermiteInterpolator::HermiteInterpolator(const std::vector<double> & dVariables, const std::vector<double> & dValues) : Interpolator(dVariables, dValues)
        {}
        
        HermitePrecomputedCoefficients::HermitePrecomputedCoefficients() : dm_1(0.0), dm_2(0.0), dm_3(0.0), dm_4(0.0)
        {}
        
        HermiteSplineCubicInterpolator::HermiteSplineCubicInterpolator(const std::vector<double> & dVariables, const std::vector<double> & dValues) : HermiteInterpolator(dVariables, dValues)
        {}
        
        HermitePrecomputedCoefficients HermiteSplineCubicInterpolator::PrecomputeCoefficients(const int & iValue1, const int & iValue2) const
        {
            HermitePrecomputedCoefficients result;
            if (iValue2 == dVariables_.size() - 1)
            {
                result.dm_1 = (dValues_.back() - dValues_.at(dVariables_.size() - 2)) / (dVariables_.back() - dVariables_.at(dVariables_.size() - 2));
            }
            else if (iValue1 == 0)
            {
                result.dm_2 = (dValues_.at(1) - dValues_.at(0)) / (dVariables_.at(1) - dVariables_.at(0));
            }
            else
            {
                result.dm_1 = (dValues_.at(iValue1 + 1) - dValues_.at(iValue1)) / (dVariables_.at(iValue1 + 1) - dVariables_.at(iValue1));
                result.dm_2 = (dValues_.at(iValue2 + 1) - dValues_.at(iValue2)) / (dVariables_.at(iValue2 + 1) - dVariables_.at(iValue2));
            }
            return result;
        }
        
        double HermiteSplineCubicInterpolator::operator()(double dVariable) const
        {
            int iIndex = Utilities::GetIndex(dVariables_, dVariable);
            if (iIndex != -1)
            {
                return ValueIfVariablePresent(iIndex);
            }
            else
            {
                int iValue1 = 0, iValue2;
                FindIndex(dVariable, iValue1);
                iValue2 = iValue1 + 1;
                
                HermitePrecomputedCoefficients coeffs = PrecomputeCoefficients(iValue1, iValue2);
                
                double t = (dVariable - dVariables_.at(iValue1)) / (dVariables_.at(iValue2) - dVariables_.at(iValue1));
                
                return Maths::HermitePolynomial3::operator()(t, 0) * dValues_.at(iValue1) + Maths::HermitePolynomial3::operator()(t, 1) * coeffs.dm_1 * (dVariables_.at(iValue2) - dVariables_.at(iValue1)) + Maths::HermitePolynomial3::operator()(t, 2) * dValues_.at(iValue2) + Maths::HermitePolynomial3::operator()(t, 3) * coeffs.dm_2 * (dVariables_.at(iValue2) - dVariables_.at(iValue1));
            }
        }
        
        double HermiteSplineCubicInterpolator::PointDerivative(double dVariable) const
        {
            int iValue1 = 0, iValue2;
            FindIndex(dVariable, iValue1);
            iValue2 = iValue1 + 1;
            
            HermitePrecomputedCoefficients coeffs = PrecomputeCoefficients(iValue1, iValue2);
            
            double t = (dVariable - dVariables_.at(iValue1)) / (dVariables_.at(iValue2) - dVariables_.at(iValue1));
            
            return Maths::HermitePolynomial3::deriv(t, 0) * dValues_.at(iValue1)
                + Maths::HermitePolynomial3::deriv(t, 1) * coeffs.dm_1 * (dVariables_.at(iValue2) - dVariables_.at(iValue1))
                + Maths::HermitePolynomial3::deriv(t, 2) * dValues_.at(iValue2)
                + Maths::HermitePolynomial3::deriv(t, 3) * coeffs.dm_2 * (dVariables_.at(iValue2) - dVariables_.at(iValue1));
        }
        
        double HermiteSplineCubicInterpolator::PointConvexity(double dVariable) const
        {
            int iValue1 = 0, iValue2;
            FindIndex(dVariable, iValue1);
            iValue2 = iValue1 + 1;
            
            HermitePrecomputedCoefficients coeffs = PrecomputeCoefficients(iValue1, iValue2);
            
            double t = (dVariable - dVariables_.at(iValue1)) / (dVariables_.at(iValue2) - dVariables_.at(iValue1));
            
            return Maths::HermitePolynomial3::deriv2(t, 0) * dValues_.at(iValue1)
            + Maths::HermitePolynomial3::deriv2(t, 1) * coeffs.dm_1 * (dVariables_.at(iValue2) - dVariables_.at(iValue1))
            + Maths::HermitePolynomial3::deriv2(t, 2) * dValues_.at(iValue2)
            + Maths::HermitePolynomial3::deriv2(t, 3) * coeffs.dm_2 * (dVariables_.at(iValue2) - dVariables_.at(iValue1));
        }
        
        HermiteDegree5Interpolator::HermiteDegree5Interpolator(const std::vector<double> & dVariables,
                                                               const std::vector<double> & dValues) : HermiteInterpolator(dVariables, dValues)
        {}
        
        HermitePrecomputedCoefficients HermiteDegree5Interpolator::PrecomputeCoefficients(const int &iValue1, const int &iValue2) const
        {
            HermitePrecomputedCoefficients result;
            if (iValue2 == dVariables_.size() - 1)
            {
                result.dm_1 = (dValues_.back() - dValues_.at(dVariables_.size() - 2)) / (dVariables_.back() - dVariables_.at(dVariables_.size() - 2));
            }
            else if (iValue1 == 0)
            {
                result.dm_2 = (dValues_.at(1) - dValues_.at(0)) / (dVariables_.at(1) - dVariables_.at(0));
            }
            else
            {
                result.dm_1 = (dValues_.at(iValue1 + 1) - dValues_.at(iValue1)) / (dVariables_.at(iValue1 + 1) - dVariables_.at(iValue1));
                result.dm_2 = (dValues_.at(iValue2 + 1) - dValues_.at(iValue2)) / (dVariables_.at(iValue2 + 1) - dVariables_.at(iValue2));
                
                result.dm_3 = (dValues_.at(iValue1 + 1) - 2 * dValues_.at(iValue1) + dValues_.at(iValue1 - 1)) / ((dVariables_.at(iValue1 + 1) - dVariables_.at(iValue1)) * (dVariables_.at(iValue1 + 1) - dVariables_.at(iValue1)));
                result.dm_4 = (dValues_.at(iValue2 + 1) - 2 * dValues_.at(iValue2) + dValues_.at(iValue2 - 1)) / ((dVariables_.at(iValue2 + 1) - dVariables_.at(iValue2)) * (dVariables_.at(iValue2 + 1) - dVariables_.at(iValue2)));
            }
            return result;
        }
        
        double HermiteDegree5Interpolator::operator()(double dVariable) const
        {
            int iIndex = Utilities::GetIndex(dVariables_, dVariable);
            if (iIndex != -1)
            {
                return ValueIfVariablePresent(iIndex);
            }
            else
            {
                int iValue1 = 0, iValue2;
                FindIndex(dVariable, iValue1);
                iValue2 = iValue1 + 1;
                
                HermitePrecomputedCoefficients coeffs = PrecomputeCoefficients(iValue1, iValue2);
                
                double delta = (dVariables_.at(iValue2) - dVariables_.at(iValue1));
                double t = (dVariable - dVariables_.at(iValue1)) / delta;
                
                return Maths::HermitePolynomial5::operator()(t, 0) * dValues_.at(iValue1)
                        + Maths::HermitePolynomial5::operator()(t, 1) * coeffs.dm_1 * delta
                        + Maths::HermitePolynomial5::operator()(t, 2) * coeffs.dm_3 * delta * delta
                        + Maths::HermitePolynomial5::operator()(t, 3) * dValues_.at(iValue2)
                        + Maths::HermitePolynomial5::operator()(t, 4) * coeffs.dm_2 * delta
                        + Maths::HermitePolynomial5::operator()(t, 5) * coeffs.dm_4 * delta * delta;
            }
        }
        
        double HermiteDegree5Interpolator::PointDerivative(double dVariable) const
        {
            int iValue1 = 0, iValue2;
            FindIndex(dVariable, iValue1);
            iValue2 = iValue1 + 1;
            
            HermitePrecomputedCoefficients coeffs = PrecomputeCoefficients(iValue1, iValue2);
            
            double delta = (dVariables_.at(iValue2) - dVariables_.at(iValue1));
            double t = (dVariable - dVariables_.at(iValue1)) / delta;
            
            return Maths::HermitePolynomial5::deriv(t, 0) * dValues_.at(iValue1)
            + Maths::HermitePolynomial5::deriv(t, 1) * coeffs.dm_1 * delta
            + Maths::HermitePolynomial5::deriv(t, 2) * coeffs.dm_3 * delta * delta
            + Maths::HermitePolynomial5::deriv(t, 3) * dValues_.at(iValue2)
            + Maths::HermitePolynomial5::deriv(t, 4) * coeffs.dm_2 * delta
            + Maths::HermitePolynomial5::deriv(t, 5) * coeffs.dm_4 * delta * delta;
        }
        
        double HermiteDegree5Interpolator::PointConvexity(double dVariable) const
        {
            int iValue1 = 0, iValue2;
            FindIndex(dVariable, iValue1);
            iValue2 = iValue1 + 1;
            
            HermitePrecomputedCoefficients coeffs = PrecomputeCoefficients(iValue1, iValue2);
            
            double delta = (dVariables_.at(iValue2) - dVariables_.at(iValue1));
            double t = (dVariable - dVariables_.at(iValue1)) / delta;
            
            return Maths::HermitePolynomial5::deriv2(t, 0) * dValues_.at(iValue1)
            + Maths::HermitePolynomial5::deriv2(t, 1) * coeffs.dm_1 * delta
            + Maths::HermitePolynomial5::deriv2(t, 2) * coeffs.dm_3 * delta * delta
            + Maths::HermitePolynomial5::deriv2(t, 3) * dValues_.at(iValue2)
            + Maths::HermitePolynomial5::deriv2(t, 4) * coeffs.dm_2 * delta
            + Maths::HermitePolynomial5::deriv2(t, 5) * coeffs.dm_4 * delta * delta;
        }
    }
}