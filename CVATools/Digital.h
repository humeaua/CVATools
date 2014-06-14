//
//  Digital.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 28/09/13.
//
//

#ifndef __CVATools__Digital__
#define __CVATools__Digital__

#include <iostream>
#include "BasePayoff.h"
#include "VanillaOptionType.h"

namespace Finance
{
    namespace Payoff
    {
        class DigitalCall : public BasePayoff1D
        {
        protected:
            double dStrike_;
        public:
            DigitalCall(double dStrike);
            
            virtual double operator()(const double s1) const;
            virtual BasePayoff1D * clone() const;
        };
        
        class DigitalPut : public BasePayoff1D
        {
        protected:
            double dStrike_;
        public:
            DigitalPut(double dStrike);
            
            virtual double operator()(double s1) const;
            virtual BasePayoff1D * clone() const;
        };
    }
}

#endif /* defined(__CVATools__Digital__) */
