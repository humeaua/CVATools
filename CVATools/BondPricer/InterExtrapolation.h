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
    }
}

#endif
