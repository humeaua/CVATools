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
        DateShifterSimple::DateShifterSimple(const int lag, const Utilities::Date::TimeUnits timeUnit, const Utilities::HolidaysPtr& holidays) : m_lag(lag), m_timeUnit(timeUnit), m_holidays(holidays)
        {}
        
        Utilities::Date::MyDate DateShifterSimple::GetFixingDate(const Utilities::Date::MyDate &input) const
        {
            return input.Add(-m_lag, m_timeUnit, *m_holidays);
        }
        
        Utilities::Date::MyDate DateShifterSimple::GetSpotDate(const Utilities::Date::MyDate &date) const
        {
            return date.Add(m_lag, m_timeUnit, *m_holidays);
        }
        
        Utilities::Date::MyDate DateShifterSimple::GetPaymentDate(const Utilities::Date::MyDate &date) const
        {
            return GetSpotDate(date);
        }
        
        Utilities::Date::MyDate DateShifterSimple::TenorDate(const Utilities::Date::MyDate &date, const Utilities::Date::MyTenor &tenor) const
        {
            return date.Add(tenor, *m_holidays);
        }
        
        const Utilities::HolidaysPtr & DateShifterSimple::getHolidays() const
        {
            return m_holidays;
        }
    }
}