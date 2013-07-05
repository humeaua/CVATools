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
#include <stdexcept>

namespace Finance
{
    namespace Instruments
    {
        DF::DF()
        {}
        
        DF::DF(const YieldCurve & sInitialYieldCurve) : YieldCurve(sInitialYieldCurve)
        {}
        
        DF::~DF()
        {}
        
        double DF::DiscountFactor(double dT) const
        {
            return exp(-dT * YC(dT));
        }
        
        double DF::DiscountFactor(const Utilities::Date::MyDate &sDate) const
        {
            double dT = sDate.Diff(sToday_);
            if (dT > 0)
            {
                return DiscountFactor(dT);
            }
            else
            {
                throw std::runtime_error("Error in discount factor : Date is before today");
            }
        }
    }
}

