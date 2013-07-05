//
//  ForwardRate.cpp
//  Seminaire
//
//  Created by Alexandre HUMEAU on 12/12/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "ForwardRate.h"
#include <stdexcept>

namespace Finance
{
    namespace Instruments
    {
        ForwardRate::ForwardRate()
        {}
        
        ForwardRate::ForwardRate(const YieldCurve & sInitialYieldCurve) : DF(sInitialYieldCurve)
        {}
        
        ForwardRate::~ForwardRate()
        {}
        
        double ForwardRate::FwdRate(double dStart, double dEnd) const
        {
            if (dStart > dEnd)
                throw std::runtime_error("ForwardRate::FwdRate : Start is after End in ForwardRate::FwdRate");
            return 1.0 / (dEnd - dStart) * (DiscountFactor(dStart) / DiscountFactor(dEnd) - 1.0);
        }
    }
}