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
        RateMarket::RateMarket(const std::string & cMarketName) : sDiscountCurve_()
        {
            Load(cMarketName);
        }
        
        void RateMarket::Load(const std::string &cMarketName)
        {}
    }
}