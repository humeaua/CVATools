//
//  RateCurve.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 21/12/13.
//
//

#ifndef __CVATools__RateCurve__
#define __CVATools__RateCurve__

#include <iostream>
#include "Underlying.h"
#include "YieldCurve.h"

namespace Finance
{
    namespace Underlyings
    {
        class RateCurve : public Underlying, public Finance::Base::YieldCurve
        {
        protected:
            virtual double Spot(const Utilities::Date::MyDate & SpotDate, const Finance::Market::Market & Market) const = 0;
            
            virtual double Forward(const Utilities::Date::MyDate & FixingDate,
                                   const Utilities::Date::MyDate & SettleDate,
                                   const Finance::Market::Market & Market) const;
            
            virtual double Spot(const Utilities::Date::MyDate & SpotDate,
                                const Finance::Market::Market & Market,
                                const ModelState & ModelState) const = 0;
            
            virtual double Forward(const Utilities::Date::MyDate & FixingDate,
                                   const Utilities::Date::MyDate & SettleDate,
                                   const Finance::Market::Market & Market,
                                   const ModelState & ModelState) const = 0;
        public:
            RateCurve(const Finance::Base::YieldCurve & DiscountCurve);
            virtual double Spot(const Utilities::Date::MyDate & SpotDate) const;
            
        };
    }
}


#endif /* defined(__CVATools__RateCurve__) */
