//
//  DateShifter.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 27/10/14.
//
//

#include "DateShifter.h"

namespace Finance
{
    namespace Base
    {
        DateShifter::DateShifter(const int & lag, const Utilities::Date::TimeUnits & timeUnit) : m_lag(lag), m_timeUnit(timeUnit)
        {}
        
        Utilities::Date::MyDate DateShifter::Shift(const Utilities::Date::MyDate &input) const
        {
            return Utilities::Date::MyDate(Utilities::Date::Add(input.Totm(), m_lag, m_timeUnit));
        }
        
    }
}