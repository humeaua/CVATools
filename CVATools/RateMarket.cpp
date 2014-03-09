//
//  RateMarket.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 19/12/13.
//
//

#include "RateMarket.h"

namespace Finance
{
    namespace Market
    {
        //  Change Constructor of Rate Market to use a real date and not necessarily the date initialized by the computer
        RateMarket::RateMarket(const std::string & cMarketName) : Finance::Base::YieldCurve(), Market(Utilities::Date::MyDate())
        {
            Load(cMarketName);
        }
        
        void RateMarket::Load(const std::string &cMarketName)
        {}
        
        RateMarket::RateMarket(const Finance::Base::YieldCurve & yc) : Finance::Market::Market(yc.Today()), Finance::Base::YieldCurve(yc)
        {}
    }
}