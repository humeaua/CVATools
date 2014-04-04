/*
 *  DiscountFactor.cpp
 *  Seminaire
 *
 *  Created by Emile on 12/12/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "DiscountFactor.h"
#include <cmath>
#include "Require.h"
#include "YieldCurve.h"
#include "Date.h"

namespace Finance
{
    namespace Instruments
    {
        DF::DF()
        {}
        
        DF::DF(const Base::YieldCurve & sInitialYieldCurve) : m_initialYieldCurve(sInitialYieldCurve)
        {}
        
        double DF::operator()(double dT) const
        {
            return exp(-dT * m_initialYieldCurve(dT));
        }
        
        double DF::operator()(const Utilities::Date::MyDate &sDate) const
        {
            double dT = sDate.Diff(Today());
            
            REQUIREEXCEPTION(dT > 0, "DF::DiscountFactor : Date is before today");
            return (*this)(dT);
        }
        
        const Utilities::Date::MyDate & DF::Today() const
        {
            return m_initialYieldCurve.Today();
        }
    }
}

