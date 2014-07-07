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
        public:
            RateCurve(const Finance::Base::YieldCurve & DiscountCurve);
            virtual double operator()(const Utilities::Date::MyDate & date1) const;
            
            virtual const Utilities::Date::MyDate & Today() const;
        };
    }
}


#endif /* defined(__CVATools__RateCurve__) */
