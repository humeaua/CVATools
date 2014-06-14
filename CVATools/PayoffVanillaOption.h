//
//  PayoffVanillaOption.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 07/04/13.
//
//

#ifndef CVATools_PayoffVanillaOption_h
#define CVATools_PayoffVanillaOption_h

#include "BasePayoff.h"
#include "VanillaOptionType.h"

namespace Finance
{
    namespace Payoff
    {
        class PayoffVanillaOption : public BasePayoff1D
        {
        protected:
            double dStrike_;
            VanillaOptionType eOptionType_;
        public:
            PayoffVanillaOption(double dStrike, VanillaOptionType eOptionType_);
            virtual ~PayoffVanillaOption();
            
            virtual double operator()(const double dS) const;
            virtual BasePayoff1D * clone() const;
        };
    }
}

#endif
