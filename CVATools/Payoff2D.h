//
//  Payoff2D.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 07/04/13.
//
//

#ifndef CVATools_Payoff2D_h
#define CVATools_Payoff2D_h

#include "EuropeanPayoff.h"

namespace Finance
{
    namespace Payoff
    {
        class Payoff2D : public EuropeanPayoff
        {
        protected:
            virtual double pay2(double s1, double s2) const = 0;
            virtual double pay1(double s1) const;
        public:
            Payoff2D();
            
            virtual ~Payoff2D();
        };
    }
}

#endif
