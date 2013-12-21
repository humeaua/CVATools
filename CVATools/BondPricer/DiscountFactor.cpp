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

namespace Finance
{
    namespace Instruments
    {
        DF::DF()
        {}
        
        DF::DF(const YieldCurve & sInitialYieldCurve) : YieldCurve(sInitialYieldCurve)
        {}
        
        double DF::operator()(double dT) const
        {
            return exp(-dT * (*this)(dT));
        }
        
        double DF::operator()(const Utilities::Date::MyDate &sDate) const
        {
            double dT = sDate.Diff(sToday_);
            
            Utilities::requireException(dT > 0, "DF::DiscountFactor : Date is before today","DF::DiscountFactor");
            return (*this)(dT);
        }
    }
}

