//
//  InterExtrapolation.h
//  Seminaire
//
//  Created by Alexandre HUMEAU on 10/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Seminaire_InterExtrapolation_h
#define Seminaire_InterExtrapolation_h

#include <vector>
#include <map>
#include "HermitePolynomials.h"

namespace Utilities
{
    namespace Interp 
    {
        class Interpolator
        {
        protected:
            std::vector<double> dVariables_;
            std::vector<double> dValues_;
            
        public:
            Interpolator(const std::vector<double> & dVariables,
                         const std::vector<double> & dValues);
            virtual double operator()(double dVariable) const = 0;
            
            void FindIndex(double dVariable, int & iValue1) const;
            virtual double ValueIfVariablePresent(int iVar) const;
            virtual size_t size() const;
        };
        
        class LinearInterpolator : public Interpolator
        {
        public:
            LinearInterpolator(const std::vector<double> & dVariables,
                               const std::vector<double> & dValues);
            virtual double operator()(double dVariable) const;
        };
        
        class LogLinDFInterpolator : public Interpolator
        {
        public:
            LogLinDFInterpolator(const std::vector<double> & dVariables,
                                 const std::vector<double> & dValues);
            virtual double operator()(double dVariable) const;
        };
        
        class NearInterpolator : public Interpolator
        {
        public:
            NearInterpolator(const std::vector<double> & dVariables,
                             const std::vector<double> & dValues);
            virtual double operator()(double dVariable) const;
            virtual void FindIndex(double dVariable, int & iValue1) const;
        };
        
        class LeftContinuousInterpolator : public Interpolator
        {
        public:
            LeftContinuousInterpolator(const std::vector<double> & dVariables,
                                       const std::vector<double> & dValues);
            virtual double operator()(double dVariable) const;
            virtual void FindIndex(double dVariables, int& iValues1) const;
        };
        
        class RightContinuousInterpolator : public Interpolator
        {
        public:
            RightContinuousInterpolator(const std::vector<double> & dVariables,
                                        const std::vector<double> & dValues);
            virtual double operator()(double dVariable) const;
        };
        
        struct HermitePrecomputedCoefficients
        {
            double dm_1, dm_2, dm_3, dm_4;
            
            HermitePrecomputedCoefficients();
        };
        
        class HermiteInterpolator : public Interpolator
        {
        public:
            HermiteInterpolator(const std::vector<double> & dVariables,
                                const std::vector<double> & dValues);
                        
            virtual double PointDerivative(double dVariable) const = 0;
        private:
            virtual HermitePrecomputedCoefficients PrecomputeCoefficients(const int & iValue1, const int & iValue2) const = 0;
        };
        
        class HermiteSplineCubicInterpolator : public HermiteInterpolator, public Maths::HermitePolynomial3
        {
        public:
            HermiteSplineCubicInterpolator(const std::vector<double> & dVariables,
                                           const std::vector<double> & dValues);
            
            virtual double operator()(double dVariable) const;
            virtual double PointDerivative(double dVariable) const;
        private:
            virtual HermitePrecomputedCoefficients PrecomputeCoefficients(const int & iValue1, const int & iValue2) const;
        };
        
        class HermiteDegree5Interpolator : public HermiteInterpolator, public Maths::HermitePolynomial5
        {
        public:
            HermiteDegree5Interpolator(const std::vector<double> & dVariables,
                                       const std::vector<double> & dValues);
            
            virtual double operator()(double dVariable) const;
            virtual double PointDerivative(double dVariable) const;
        private:
            virtual HermitePrecomputedCoefficients PrecomputeCoefficients(const int & iValue1, const int & iValue2) const;
        };
    }
}

#endif
