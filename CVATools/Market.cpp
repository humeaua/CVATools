//
//  Market.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 08/12/13.
//
//

#include "Market.h"

namespace Finance
{
    namespace Market
    {
        Market::Market(const Utilities::Date::MyDate & TodayDate) : TodayDate_(TodayDate)
        {}
        
        const Utilities::Date::MyDate& Market::TodayDate() const
        {
            return TodayDate_;
        }
        
        Utilities::Date::MyDate & Market::TodayDate()
        {
            return TodayDate_;
        }
    }
}