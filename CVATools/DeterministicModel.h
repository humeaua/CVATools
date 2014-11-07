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
#include <tr1/memory>

namespace Finance
{
    namespace Market
    {
        class Market;
    }
    namespace Models
    {
        class DeterministicModel : public Models::Model
        {
        protected:
            std::tr1::shared_ptr<Market::Market> m_Market;
        public:
            virtual Finance::Underlyings::RateCurve & GetRateCurve(const std::string & currency) const;
            virtual double GetFXSpot(const std::string & domesticCurrency, const std::string & foreignCurrency) const;

        };
    }
}

#endif /* defined(__CVATools__DeterministicModel__) */
