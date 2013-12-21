//
//  ForwardRate.cpp
//  Seminaire
//
//  Created by Alexandre HUMEAU on 12/12/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "ForwardRate.h"
#include "Require.h"

namespace Finance
{
    namespace Instruments
    {
        ForwardRate::ForwardRate(const YieldCurve & sInitialYieldCurve) : DF(sInitialYieldCurve)
        {}
        
        double ForwardRate::FwdRate(double dStart, double dEnd) const
        {
            Utilities::requireException(dStart < dEnd, "Start is after End","ForwardRate::FwdRate");
            return 1.0 / (dEnd - dStart) * ((*this)(dStart) / (*this)(dEnd) - 1.0);
        }
    }
}