//
//  PutSpread.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 28/09/13.
//
//

#ifndef __CVATools__PutSpread__
#define __CVATools__PutSpread__

#include <iostream>
#include "Payoff.h"

namespace Finance
{
    namespace Payoff
    {
        class PutSpread : public Payoff
        {
        protected:
            double dStrike_, dLeftSpread_, dRightSpread_;
        public:
            PutSpread(double dStrike, double dLeftSpread, double dRightSpread);
            
            virtual double pay(double s1) const;
        };
    }
}

#endif /* defined(__CVATools__PutSpread__) */
