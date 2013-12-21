//
//  FXMarket.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 21/12/13.
//
//

#include "FXMarket.h"

namespace Finance
{
    namespace Market
    {
        //  Change the constructor to use a correct string to load
        FXMarket::FXMarket(const std::string & cMarketName) : Market(Utilities::Date::MyDate()), DomesticRateMarket("")
        {
            Load(cMarketName);
        }
        
        void FXMarket::Load(const std::string &cMarketName)
        {}
    }
}