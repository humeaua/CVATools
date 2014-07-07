//
//  ForeignExchangeRate.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 21/12/13.
//
//

#include "ForeignExchangeRate.h"

namespace Finance
{
    namespace Underlyings
    {
        double ForeignExchangeRate::operator()(const Utilities::Date::MyDate & date1) const
        {
            return dSpot;
        }
        
        double ForeignExchangeRate::operator()(const Utilities::Date::MyDate & date1,
                                               const Utilities::Date::MyDate & date2) const
        {
            //  default rule : add 2 business days to get the spot date from today
            return dSpot * DomesticDiscountCurve(date1) / ForeignDiscountCurve(date1) * ForeignDiscountCurve(date2) / DomesticDiscountCurve(date2);
        }
    }
}
