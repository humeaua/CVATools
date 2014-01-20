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
        typedef enum
        {
            LIN,
            NEAR, 
            RIGHT_CONTINUOUS,
            LEFT_CONTINUOUS,
            SPLINE_CUBIC,
            RAW,
            HERMITE_SPLINE_CUBIC
        }InterExtrapolationType;
        
        class InterExtrapolation1D
        {
        protected:
            InterExtrapolationType eInterpolationType_;
            std::vector<double> dVariables_;
            std::vector<double> dValues_;
            std::size_t iNValues_;
            
        private:
            //  Vector of second derivative values used for spline cubic interpolation
            std::vector<double> dSecondDerivativeValues_;
            
            virtual double ExtrapolateLocal(double dVariable, size_t iIndex0, size_t iIndex1) const;
            virtual double ExtrapolateLeft(double dVariable) const;
            virtual double ExtrapolateRight(double dVariable) const;
            virtual double Extrapolate(double dVariable) const;
            
        public:
            InterExtrapolation1D();
            InterExtrapolation1D(const std::vector<double> & dVariables,
                                 const std::vector<double> & dValues,
                                 InterExtrapolationType eInterpolationType);
            
            virtual double operator()(double dValue) const;
        };
        
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
