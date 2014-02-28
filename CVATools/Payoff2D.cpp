//
//  Payoff2D.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 07/04/13.
//
//

#include "Payoff2D.h"
#include "Exception.h"

namespace Finance
{
    namespace Payoff
    {
        Payoff2D::Payoff2D() : EuropeanPayoff(2)
        {}
        
        Payoff2D::~Payoff2D()
        {}
        
        double Payoff2D::pay1(double s1) const
        {
            throw EXCEPTION("Method not needed");
        }
    }
}