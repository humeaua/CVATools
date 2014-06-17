//
//  DeterministicModel.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 08/03/14.
//
//

#ifndef __CVATools__DeterministicModel__
#define __CVATools__DeterministicModel__

#include <iostream>
#include "FXMarket.h"
#include "Model.h"

namespace Finance
{
    namespace Models
    {
        class DeterministicModel : public Finance::Market::FXMarket, public Models::Model
        {
        public:
            virtual Finance::Underlyings::RateCurve & GetRateCurve(const std::string & currency) const;
            virtual double GetFXSpot(const std::string & domesticCurrency, const std::string & foreignCurrency) const;

        };
    }
}

#endif /* defined(__CVATools__DeterministicModel__) */
