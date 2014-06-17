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
            std::vector<double> SpotFXs;
        public:
            FXMarket(const std::string & cMarketName);
            FXMarket(const RateMarket& DomesticRateMarket,
                     const std::vector<RateMarket> & ForeignRateMarkets,
                     const std::vector<double> & SpotFxs,
                     const Utilities::Date::MyDate & Today);
            
            virtual double GetSpot(const std::string & foreignCurrency, const std::string & domesticCurrency) const;
        protected:
            virtual void Load(const std::string & cMarketName);
            
            size_t FindYCIndex(const std::string & ccy) const;
        };
    }
}

#endif /* defined(__CVATools__FXMarket__) */
