//
//  Underlying.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 08/12/13.
//
//

#ifndef __CVATools__Underlying__
#define __CVATools__Underlying__

#include <iostream>
#include "Date.h"
#include "Market.h"

/*
 This class implements the base class of an underlying 
 */

namespace Finance
{
    namespace Underlyings
    {
        class Underlying
        {
        protected:
            virtual double Spot(const Utilities::Date::MyDate & SpotDate, const Finance::Market::Market & sMarket) const = 0;
            
            virtual double Forward(const Utilities::Date::MyDate & FixingDate,
                                   const Utilities::Date::MyDate & SettleDate,
                                   const Finance::Market::Market & sMarket) const = 0;
        };
    }
}

#endif /* defined(__CVATools__Underlying__) */
