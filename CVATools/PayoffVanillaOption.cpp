//
//  PayoffVanillaOption.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 07/04/13.
//
//

#include "PayoffVanillaOption.h"
#include <iostream>
#include <cmath>
#include "Exception.h"

namespace Finance
{
    namespace Payoff
    {
        PayoffVanillaOption::PayoffVanillaOption(double dStrike, VanillaOptionType eOptionType) : dStrike_(dStrike), eOptionType_(eOptionType)
        {}
        
        PayoffVanillaOption::~PayoffVanillaOption()
        {}
        
        double PayoffVanillaOption::operator()(const double dS) const
        {
            switch (eOptionType_)
            {
                case CALL:
                {
                    return std::max(dS - dStrike_, 0.0);
                }
                case PUT:
                {
                    return std::max(dStrike_ - dS, 0.0);
                }
                case STRADDLE:
                {
                    return fabs(dStrike_ - dS);
                }
                default:
                {
                    throw EXCEPTION("Option Type not understood");
                }
            }
        }
        
        BasePayoff1D * PayoffVanillaOption::clone() const
        {
            return new PayoffVanillaOption(*this);
        }
    }
}