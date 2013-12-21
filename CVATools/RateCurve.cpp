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
        RateCurve::RateCurve(const Finance::Base::YieldCurve & DiscountCurve) : DiscountCurve_(DiscountCurve)
        {}

        //  Computation of spot discount factor
        double RateCurve::Spot(const Utilities::Date::MyDate &SpotDate, const Finance::Market::Market &Market) const
        {
            //  Assuming ACT365FIXED day count convention for discount factors
            double dt = SpotDate.Diff(Market.TodayDate());
            return exp(-DiscountCurve_(dt) * dt);
        }
        
        //  Computation of forward discount factor
        double RateCurve::Forward(const Utilities::Date::MyDate &FixingDate, const Utilities::Date::MyDate &SettleDate, const Finance::Market::Market &Market) const
        {
            return Spot(SettleDate, Market) / Spot(FixingDate, Market);
        }
    }
}