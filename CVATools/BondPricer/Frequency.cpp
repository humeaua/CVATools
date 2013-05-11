//
//  Frequency.cpp
//  Seminaire
//
//  Created by Alexandre HUMEAU on 23/01/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Frequency.h"

namespace Finance {
    
    std::pair<std::size_t, Utilities::Date::TimeUnits> Frequency::ParseFrequency(MyFrequency eFrequency)
    {
        if (eFrequency == MyFrequencyAnnual)
        {
            return std::make_pair(1, Utilities::Date::YEAR);
        }
        else if (eFrequency == MyFrequencyMonthly)
        {
            return std::make_pair(1, Utilities::Date::MONTH);
        }
        else if (eFrequency == MyFrequencyQuarterly)
        {
            return std::make_pair(3, Utilities::Date::MONTH);
        }
        else if (eFrequency == MyFrequencySemiannual)
        {
            return std::make_pair(6, Utilities::Date::MONTH);
        }
        else
        {
            throw "Unknown frequency in Parse Frequency";
        }
    }
    
}