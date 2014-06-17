//
//  FXMarket.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 21/12/13.
//
//

#include "FXMarket.h"
#include "Require.h"

namespace Finance
{
    namespace Market
    {
        //  Change the constructor to use a correct string to load
        FXMarket::FXMarket(const std::string & cMarketName) : Market(Utilities::Date::MyDate()), DomesticRateMarket(""), ForeignRateMarkets(std::vector<RateMarket>(0, RateMarket("")))
        {
            Load(cMarketName);
        }
        
        FXMarket::FXMarket(const RateMarket& DomesticRateMarket0,
                           const std::vector<RateMarket> & ForeignRateMarkets0,
                           const std::vector<double> & SpotFxs0,
                           const Utilities::Date::MyDate & Today)
        : DomesticRateMarket(DomesticRateMarket0), ForeignRateMarkets(ForeignRateMarkets0), SpotFXs(SpotFxs0), Finance::Market::Market(Today)
        {
            REQUIREEXCEPTION(ForeignRateMarkets.size() == SpotFxs0.size(), "Foreign Markets and spot fx do not have the same size");
        }
        
        void FXMarket::Load(const std::string &cMarketName)
        {}
        
        double FXMarket::GetSpot(const std::string &foreignCurrency, const std::string &domesticCurrency) const
        {
            const size_t forCcyIndex = FindYCIndex(foreignCurrency);
            
            if (domesticCurrency == DomesticRateMarket.Ccy())
            {
                return SpotFXs.at(forCcyIndex);
            }
            else
            {
                const size_t domCcyIndex = FindYCIndex(domesticCurrency);
                // FOR/DOM fx spot = FOR/common * common/DOM
                return SpotFXs.at(forCcyIndex) / SpotFXs.at(domCcyIndex);
            }
        }
        
        size_t FXMarket::FindYCIndex(const std::string &ccy) const
        {
            for (std::size_t i = 0 ; i < ForeignRateMarkets.size() ; ++i)
            {
                if (ccy == ForeignRateMarkets[i].Ccy())
                {
                    return i;
                }
            }
            throw EXCEPTION("YC index is not found");
        }
    }
}