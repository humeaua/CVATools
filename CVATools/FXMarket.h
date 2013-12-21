//
//  FXMarket.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 21/12/13.
//
//

#ifndef __CVATools__FXMarket__
#define __CVATools__FXMarket__

#include <iostream>
#include "Market.h"
#include "RateMarket.h"

namespace Finance
{
    namespace Market
    {
        
        class FXMarket : public Market
        {
        private:
            RateMarket DomesticRateMarket;
            std::vector<RateMarket> ForeignRateMarkets;
        public:
            FXMarket(const std::string & cMarketName);
            
            virtual void Load(const std::string & cMarketName);
        };
    }
}

#endif /* defined(__CVATools__FXMarket__) */
