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

namespace Finance
{
    namespace Payoff
    {
        class Digital : public Payoff
        {
        protected:
            double dStrike_, dLeftSpread_, dRightSpread_;
            VanillaOptionType eOptionType_;
        public:
            Digital(double dStrike, double dLeftSpread, double dRightSpread, VanillaOptionType eOptionType);
            
            double pay(double s1) const;
        };
    }
}

#endif /* defined(__CVATools__Digital__) */
