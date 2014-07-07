//
//  Inflation.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 28/12/13.
//
//

#include "Inflation.h"

namespace Finance
{
    namespace Underlyings
    {
        double Inflation::operator()(const Utilities::Date::MyDate & date1) const
        {
            return dSpot;
        }
        
        double Inflation::operator()(const Utilities::Date::MyDate & date1,
                                     const Utilities::Date::MyDate & date2) const
        {
            //  default rule : add 2 business days to get the spot date from today
            return dSpot * NominalCurve(date1) / RealCurve(date1) * RealCurve(date2) / NominalCurve(date2);
        }
    }
}