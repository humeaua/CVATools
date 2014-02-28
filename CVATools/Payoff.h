//
//  Payoff.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 07/04/13.
//
//

#ifndef CVATools_Payoff_h
#define CVATools_Payoff_h

#include "EuropeanPayoff.h"

namespace Finance
{
    namespace Payoff
    {
        class Payoff : public EuropeanPayoff
        {
        protected:
            virtual double pay1(double s1) const = 0;
            virtual double pay2(double s1, double s2) const;
        public:
            Payoff();
            virtual ~Payoff();
        };
    }
}

#endif
