//
//  Underlying.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 08/12/13.
//
//

#include "Underlying.h"

namespace Finance
{
    namespace Underlyings
    {
        double Underlying::operator()(const Utilities::Date::MyDate &date1, const Utilities::Date::MyDate &date2) const
        {
            return (*this)(date2) / (*this)(date1);
        }
    }
}