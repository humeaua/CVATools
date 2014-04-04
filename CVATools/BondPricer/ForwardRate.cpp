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
        ForwardRate::ForwardRate(const Base::YieldCurve & sInitialYieldCurve) : m_discountFactor(sInitialYieldCurve)
        {}
        
        double ForwardRate::FwdRate(double dStart, double dEnd) const
        {
            REQUIREEXCEPTION(dStart < dEnd, "Start is after End");
            return 1.0 / (dEnd - dStart) * (m_discountFactor(dStart) / m_discountFactor(dEnd) - 1.0);
        }
        
        double ForwardRate::FwdRate(const Utilities::Date::MyDate &start, const Utilities::Date::MyDate &end) const
        {
            return FwdRate(start.Diff(Today()), end.Diff(Today()));
        }
        
        const Utilities::Date::MyDate & ForwardRate::Today() const
        {
            return m_discountFactor.Today();
        }
    }
}