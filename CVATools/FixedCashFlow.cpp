//
//  FixedCashFlow.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 01/03/14.
//
//

#include "FixedCashFlow.h"

namespace Finance
{
    namespace Deal
    {
        FixedCashFlow::FixedCashFlow(double amount, const std::string & currency, const Utilities::Date::MyDate & payDate) : m_dAmount(amount), m_Currency(currency), m_payDate(payDate)
        {}
        
        double FixedCashFlow::Price(const Finance::Models::Model &model, const std::string & reportingCurrency) const
        {
            const Finance::Underlyings::RateCurve & reportingCurrencyRateCurve = model.GetRateCurve(reportingCurrency);
            
            //  conversion via spot
            const double fxspot = model.GetFXSpot(reportingCurrency, m_Currency);
            
            return reportingCurrencyRateCurve.Spot(m_payDate) * fxspot * m_dAmount;
        }
    }
}