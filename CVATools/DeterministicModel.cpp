//
//  DeterministicModel.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 08/03/14.
//
//

#include "DeterministicModel.h"
#include "Exception.h"

namespace Finance
{
    namespace Models
    {
        double DeterministicModel::GetFXSpot(const std::string &domesticCurrency, const std::string &foreignCurrency) const
        {
            if (Market::FXMarket * fxMarket = dynamic_cast<Market::FXMarket*>(m_Market.get()))
            {
                return fxMarket->GetSpot(foreignCurrency, domesticCurrency);
            }
            else
            {
                throw EXCEPTION("Cannot dynamic_cast market to Market::FXMarket");
            }
        }
    }
}