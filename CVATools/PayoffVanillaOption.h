//
//  PayoffVanillaOption.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 07/04/13.
//
//

#ifndef CVATools_PayoffVanillaOption_h
#define CVATools_PayoffVanillaOption_h

#include "Payoff.h"
#include "VanillaOptionType.h"

namespace Finance
{
    namespace Payoff
    {
        class PayoffVanillaOption : public Payoff
        {
        protected:
            double dStrike_;
            VanillaOptionType eOptionType_;
        public:
            PayoffVanillaOption(double dStrike, VanillaOptionType eOptionType_);
            virtual ~PayoffVanillaOption();
            
            virtual double pay(double dS) const;
        };
    }
}

#endif
