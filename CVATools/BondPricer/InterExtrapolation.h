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
            SPLINE_CUBIC
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
            
        public:
            InterExtrapolation1D();
            InterExtrapolation1D(const std::vector<double> & dVariables,
                                 const std::vector<double> & dValues,
                                 InterExtrapolationType eInterpolationType);
            virtual ~InterExtrapolation1D();
            
            double Interp1D(double dValue) const;
        };
        
        struct InterExtrapolationnD
        {
        protected:
            InterExtrapolationType eInterpolationType_;
            std::size_t iNDimensions_;
            std::size_t iNValues_;
            std::map<std::size_t, std::vector<double> > dVariables_;
            std::map<std::size_t, std::vector<double> > dValues_;
            
        public:
            InterExtrapolationnD();
            InterExtrapolationnD(const std::map<std::size_t, std::vector<double> > & dVariables,
                                 const std::map<std::size_t, std::vector<double> > & dValues,
                                 InterExtrapolationType eInterpolationType);
            
            std::map<std::size_t, double> InterpnD(const std::map<size_t, double> & dValue);
        };
    }
}


#endif
