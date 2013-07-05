//
//  Payoff.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 07/04/13.
//
//

#ifndef CVATools_Payoff_h
#define CVATools_Payoff_h

namespace Finance
{
    namespace Payoff
    {
        class Payoff
        {
        public:
            Payoff();
            virtual ~Payoff();
            
            virtual double pay(double s1) const = 0;
        };
    }
}

#endif
