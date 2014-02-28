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
            
            virtual double pay1(double s1) const;
        public:
            PutSpread(double dStrike, double dLeftSpread, double dRightSpread);
        };
    }
}

#endif /* defined(__CVATools__PutSpread__) */
