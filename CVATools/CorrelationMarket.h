//
//  CorrelationMarket.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 20/12/13.
//
//

#ifndef __CVATools__CorrelationMarket__
#define __CVATools__CorrelationMarket__

#include <iostream>
#include "Market.h"
#include <map>
#include "CorrelationTS.h"

namespace Finance
{
    namespace Market
    {
        typedef enum {
            //  Need the reverse as well as the correlation are symmetric
            CorrelationType_NULL,
            CorrelationType_EquityRate,
            CorrelationType_EquityFX,
            CorrelationType_RateEquity,
            CorrelationType_RateFX,
            CorrelationType_FXRate,
            CorrelationType_FXEquity
        }CorrelationTypeEnum;
        
        class CorrelationKey
        {
        public:
            CorrelationKey();
            CorrelationKey(const std::string & cLabel1, const std::string & cLabel2, const CorrelationTypeEnum & eCorrelationType);
            CorrelationKey(const CorrelationKey & sCorrelationKey);
            
            //  Getters and setters
            virtual std::string Label1() const ;
            virtual std::string Label2() const ;
            virtual CorrelationTypeEnum CorrelationType() const ;
            
            virtual bool operator < (const CorrelationKey & rhs) const;

        private:
            CorrelationTypeEnum eCorrelationType_;
            std::string cLabel1_;
            std::string cLabel2_;
        };
        
        inline bool operator==(const CorrelationKey& lhs, const CorrelationKey& rhs);
        
        class CorrelationMarket : public Market::Market
        {
            std::map<std::pair<CorrelationKey, CorrelationKey>, Finance::Base::CorrelationTS> sMarket;
            
        protected:
            virtual void Load(const std::string & cMarketName);
        public:
            virtual void Add(const CorrelationKey & sElmt1, const CorrelationKey & sElmt2, const Finance::Base::CorrelationTS & sCorrelTS);
        };
    }
}

#endif /* defined(__CVATools__CorrelationMarket__) */
