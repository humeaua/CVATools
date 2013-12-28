//
//  CorrelationMarket.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 20/12/13.
//
//

#include "CorrelationMarket.h"

namespace Finance
{
    namespace Market
    {
        CorrelationKey::CorrelationKey() : eCorrelationType_(CorrelationType_NULL)
        {}
        
        CorrelationKey::CorrelationKey(const std::string & cLabel1, const std::string & cLabel2, const CorrelationTypeEnum & eCorrelationType) : cLabel1_(cLabel1), cLabel2_(cLabel2), eCorrelationType_(eCorrelationType)
        {}
        
        CorrelationKey::CorrelationKey(const CorrelationKey & sCorrelationKey)
        {
            *this = sCorrelationKey;
        }
        
        std::string CorrelationKey::Label1() const
        {
            return cLabel1_;
        }
        
        std::string CorrelationKey::Label2() const
        {
            return  cLabel2_;
        }
        
        CorrelationTypeEnum CorrelationKey::CorrelationType() const
        {
            return eCorrelationType_;
        }
        
        bool CorrelationKey::operator<(const Finance::Market::CorrelationKey &rhs) const
        {
            return cLabel1_ < rhs.Label1() || (cLabel1_ == rhs.Label1() && cLabel2_ < rhs.Label2());
        }
        
        inline bool operator==(const CorrelationKey& lhs, const CorrelationKey& rhs)
        {
            return lhs.Label1() == rhs.Label1() && lhs.Label2() == rhs.Label2() && lhs.CorrelationType() == rhs.CorrelationType();
        }
        
        void CorrelationMarket::Add(const Finance::Market::CorrelationKey &sElmt1, const Finance::Market::CorrelationKey &sElmt2, const Finance::Base::CorrelationTS &sCorrelTS)
        {
            if (sMarket.count(std::make_pair(sElmt1, sElmt2)) != 0)
            {
                sMarket.find(std::make_pair(sElmt1, sElmt2))->second = sCorrelTS;
            }
            else
            {
                sMarket[std::make_pair(sElmt1, sElmt2)] = sCorrelTS;
            }
        }
        
        //  To be implemented
        void CorrelationMarket::Load(const std::string &cMarketName)
        {}
    }
}