//
//  DeterministicModel.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 08/03/14.
//
//

#include "DeterministicModel.h"

namespace Finance
{
    namespace Models
    {
        double DeterministicModel::GetFXSpot(const std::string &domesticCurrency, const std::string &foreignCurrency) const
        {
            return Finance::Market::FXMarket::GetSpot(foreignCurrency, domesticCurrency);
        }
    }
}