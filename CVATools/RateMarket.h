//
//  RateMarket.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 19/12/13.
//
//

#ifndef __CVATools__RateMarket__
#define __CVATools__RateMarket__

#include <iostream>
#include "Market.h"
#include "YieldCurve.h"

namespace Finance
{
    namespace Market
    {
        class RateMarket : public Market
        {
        protected:
            Finance::Base::YieldCurve sDiscountCurve_;
            
            virtual void Load(const std::string & cMarketName);
        public:
            RateMarket(const std::string & cMarketName);
        };
    }
}

#endif /* defined(__CVATools__RateMarket__) */
