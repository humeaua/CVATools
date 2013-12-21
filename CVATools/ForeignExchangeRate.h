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
        template<typename Curve>
        class ForeignExchangeRate : public Underlying
        {
        protected:
            virtual double Spot(const Utilities::Date::MyDate & SpotDate, const Finance::Market::Market & FXMarket) const
            {
                return dSpot;
            }
            
            virtual double Forward(const Utilities::Date::MyDate & FixingDate,
                                   const Utilities::Date::MyDate & SettleDate,
                                   const Finance::Market::Market & Market) const
            {
                return dSpot * ForeignDiscountCurve(FixingDate) / DomesticDiscountCurve(FixingDate);
            }
            
            virtual double Spot(const Utilities::Date::MyDate & SpotDate,
                                const Finance::Market::Market & Market,
                                const ModelState & ModelState) const = 0;
            
            virtual double Forward(const Utilities::Date::MyDate & FixingDate,
                                   const Utilities::Date::MyDate & SettleDate,
                                   const Finance::Market::Market & Market,
                                   const ModelState & ModelState) const = 0;
        private:
            double dSpot;
            Curve DomesticDiscountCurve, ForeignDiscountCurve;
        };
    }
}

#endif /* defined(__CVATools__ForeignExchangeRate__) */
