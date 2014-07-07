//
//  RateCurve.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 21/12/13.
//
//

#include "RateCurve.h"
#include <cmath>

namespace Finance
{
    namespace Underlyings
    {
        RateCurve::RateCurve(const Finance::Base::YieldCurve & DiscountCurve) : Finance::Base::YieldCurve(DiscountCurve)
        {}

        //  Computation of spot discount factor
        double RateCurve::operator()(const Utilities::Date::MyDate & date1) const
        {
            //  Assuming ACT365FIXED day count convention for discount factors
            double dt = date1.Diff(Finance::Base::YieldCurve::Today());
            return exp(-Finance::Base::YieldCurve::operator()(dt) * dt);
        }
        
        const Utilities::Date::MyDate & RateCurve::Today() const
        {
            return Base::YieldCurve::Today();
        }
    }
}