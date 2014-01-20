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
            
            virtual void FindIndex(double dVariable, int & iValue1, int& iValue2) const;
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
            virtual void FindIndex(double dVariable, int & iValue1, int& iValue2) const;
        };
        
        class LeftContinuousInterpolator : public Interpolator
        {
        public:
            LeftContinuousInterpolator(const std::vector<double> & dVariables,
                                       const std::vector<double> & dValues);
            virtual double operator()(double dVariable) const;
            virtual void FindIndex(double dVariable, int & iValue1, int& iValue2) const;
        };
        
        class RightContinuousInterpolator : public Interpolator
        {
        public:
            RightContinuousInterpolator(const std::vector<double> & dVariables,
                                        const std::vector<double> & dValues);
            virtual double operator()(double dVariable) const;
            virtual void FindIndex(double dVariable, int & iValue1, int& iValue2) const;
        };
        
        class SplineCubicInterpolator : public Interpolator
        {
        protected:
            std::vector<double> dSecondDerivativeValues_;
        public:
            SplineCubicInterpolator(const std::vector<double> & dVariables,
                                    const std::vector<double> & dValues);
            virtual double operator()(double dVariable) const;
        };
        
        class HermiteSplineCubicInterpolator : public Interpolator
        {
        public:
            HermiteSplineCubicInterpolator(const std::vector<double> & dVariables,
                                           const std::vector<double> & dValues);
            virtual double operator()(double dVariable) const;
        };
    }
}

#endif
