//
//  CallSpread.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 28/09/13.
//
//

#ifndef __CVATools__CallSpread__
#define __CVATools__CallSpread__

#include <iostream>
#include "Payoff.h"

namespace Finance
{
    namespace Payoff
    {
        class CallSpread : public Payoff
        {
        protected:
            double dStrike_, dLeftSpread_, dRightSpread_;
            
            virtual double pay1(double s1) const;
        public:
            CallSpread(double dStrike, double dLeftSpread, double dRightSpread);
        };
    }
}

#endif /* defined(__CVATools__CallSpread__) */
