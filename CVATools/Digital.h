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
#include "Payoff.h"
#include "VanillaOptionType.h"

namespace Finance
{
    namespace Payoff
    {
        class DigitalCall : public Payoff
        {
        protected:
            double dStrike_;
            
            double pay1(double s1) const;
        public:
            DigitalCall(double dStrike);
        };
        
        class DigitalPut : public Payoff
        {
        protected:
            double dStrike_;
            
            double pay1(double s1) const;
        public:
            DigitalPut(double dStrike);
        };
    }
}

#endif /* defined(__CVATools__Digital__) */
