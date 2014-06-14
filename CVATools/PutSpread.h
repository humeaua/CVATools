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
#include "BasePayoff.h"

namespace Finance
{
    namespace Payoff
    {
        class PutSpread : public BasePayoff1D
        {
        protected:
            double dStrike_, dLeftSpread_, dRightSpread_;
        public:
            PutSpread(double dStrike, double dLeftSpread, double dRightSpread);
            
            virtual double operator()(const double s1) const;
            virtual BasePayoff1D * clone() const;
        };
    }
}

#endif /* defined(__CVATools__PutSpread__) */
