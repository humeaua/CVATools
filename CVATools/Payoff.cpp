//
//  Payoff.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 07/04/13.
//
//

#include "Payoff.h"
#include "Exception.h"

namespace Finance
{
    namespace Payoff
    {
        Payoff::Payoff() : EuropeanPayoff(1)
        {}
        
        Payoff::~Payoff()
        {}
        
        double Payoff::pay2(double s1, double s2) const
        {
            throw EXCEPTION("Method not needed");
        }
    }
}