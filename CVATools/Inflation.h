//
//  Inflation.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 28/12/13.
//
//

#ifndef __CVATools__Inflation__
#define __CVATools__Inflation__

#include <iostream>
#include "Underlying.h"
#include "RateCurve.h"

namespace Finance
{
    namespace Underlyings
    {
        template<typename Curve>
        class Inflation : public Underlying
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
                //  default rule : add 2 business days to get the spot date from today
                Utilities::Date::MyDate SpotDate = NominalCurve.Today().Add(2, Utilities::Date::BUSINESSDAY);
                return dSpot * NominalCurve(SpotDate) / RealCurve(SpotDate) * RealCurve(SettleDate) / NominalCurve(SettleDate);
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
            Curve NominalCurve, RealCurve;
        };
    }
}

#endif /* defined(__CVATools__Inflation__) */
