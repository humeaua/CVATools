//
//  ForeignExchangeRate.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 21/12/13.
//
//

#ifndef __CVATools__ForeignExchangeRate__
#define __CVATools__ForeignExchangeRate__

#include <iostream>
#include "Underlying.h"
#include "RateCurve.h"

namespace Finance
{
    namespace Underlyings
    {
        class ForeignExchangeRate : public Underlying
        {
        protected:
            virtual double operator()(const Utilities::Date::MyDate & date1) const;
            virtual double operator()(const Utilities::Date::MyDate & date1,
                                      const Utilities::Date::MyDate & date2) const;
            
        private:
            double dSpot;
            RateCurve DomesticDiscountCurve, ForeignDiscountCurve;
        };
    }
}

#endif /* defined(__CVATools__ForeignExchangeRate__) */
