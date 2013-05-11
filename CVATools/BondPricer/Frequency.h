//
//  Frequency.h
//  Seminaire
//
//  Created by Alexandre HUMEAU on 23/01/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef Seminaire_Frequency_h
#define Seminaire_Frequency_h

#include "Date.h"

namespace Finance {
    typedef enum
    {
        MyFrequencyAnnual,
        MyFrequencySemiannual,
        MyFrequencyQuarterly,
        MyFrequencyMonthly
    }MyFrequency;

    class Frequency{
    public:
        static std::pair<std::size_t, Utilities::Date::TimeUnits> ParseFrequency(MyFrequency eFrequency);
    };
    
}

#endif
