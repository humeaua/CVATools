//
//  Payoff2D.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 07/04/13.
//
//

#ifndef CVATools_Payoff2D_h
#define CVATools_Payoff2D_h

namespace Finance
{
    namespace Payoff
    {
        class Payoff2D
        {
        public:
            virtual double pay(double s1, double s2) const = 0;
        };
    }
}

#endif
