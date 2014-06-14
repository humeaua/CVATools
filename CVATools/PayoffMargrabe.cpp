//
//  PayoffMargrabe.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 13/04/13.
//
//

#include "PayoffMargrabe.h"
#include <iostream>

namespace Finance
{
    namespace Payoff
    {
        PayoffMargrabe::PayoffMargrabe(double dK) : dK_(dK)
        {}
        
        double PayoffMargrabe::operator()(const double s1, const double s2) const
        {
            return std::max(s1 - dK_ * s2, 0.0);
        }
        
        BasePayoff2D * PayoffMargrabe::clone() const
        {
            return new PayoffMargrabe(*this);
        }
    }
}