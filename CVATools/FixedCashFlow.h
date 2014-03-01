//
//  FixedCashFlow.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 01/03/14.
//
//

#ifndef __CVATools__FixedCashFlow__
#define __CVATools__FixedCashFlow__

#include <iostream>
#include "Leg.h"
#include "Date.h"

namespace Finance
{
    namespace Deal
    {
        class FixedCashFlow : public Leg
        {
        protected:
            double m_dAmount;
            std::string m_Currency;
            Utilities::Date::MyDate m_payDate;
        public:
            FixedCashFlow(double amount, const std::string & currency, const Utilities::Date::MyDate & payDate);
            
            virtual double Price(const Finance::Models::Model & model, const std::string & reportingCurrency) const;
        };
    }
}

#endif /* defined(__CVATools__FixedCashFlow__) */
