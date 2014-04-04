//
//  Digital.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 28/09/13.
//
//

#include "Digital.h"
#include "Require.h"

namespace Finance
{
    namespace Payoff
    {
        DigitalCall::DigitalCall(double dStrike) : dStrike_(dStrike)
        {}
        
        double DigitalCall::pay1(double s1) const
        {
            if (s1 > dStrike_)
            {
                return 1.0;
            }
            else
            {
                return 0.0;
            }
        }
        
        DigitalPut::DigitalPut(double strike) : dStrike_(strike)
        {}
        
        double DigitalPut::pay1(double s1) const
        {
            if (s1 < dStrike_)
            {
                return 1.0;
            }
            else
            {
                return 0.0;
            }
        }
    }
}