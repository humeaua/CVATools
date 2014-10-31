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
        DateShifterSimple::DateShifterSimple(const int & lag, const Utilities::Date::TimeUnits & timeUnit) : m_lag(lag), m_timeUnit(timeUnit)
        {}
        
        Utilities::Date::MyDate DateShifterSimple::GetFixingDate(const Utilities::Date::MyDate &input) const
        {
            return Utilities::Date::MyDate(Utilities::Date::Add(input.Totm(), -m_lag, m_timeUnit));
        }
        
        Utilities::Date::MyDate DateShifterSimple::GetSpotDate(const Utilities::Date::MyDate &date) const
        {
            return Utilities::Date::MyDate(Utilities::Date::Add(date.Totm(), m_lag, m_timeUnit));
        }
        
        Utilities::Date::MyDate DateShifterSimple::GetPaymentDate(const Utilities::Date::MyDate &date) const
        {
            return GetSpotDate(date);
        }
        
        Utilities::Date::MyDate DateShifterSimple::TenorDate(const Utilities::Date::MyDate &date, const Utilities::Date::MyTenor &tenor) const
        {
            return date.Add(tenor);
        }
        
        Utilities::Date::MyDate DateShifterDummy::GetFixingDate(const Utilities::Date::MyDate &date) const
        {
            return date;
        }
        
        Utilities::Date::MyDate DateShifterDummy::GetSpotDate(const Utilities::Date::MyDate &date) const
        {
            return date;
        }
        
        Utilities::Date::MyDate DateShifterDummy::GetPaymentDate(const Utilities::Date::MyDate &date) const
        {
            return date;
        }
        
        Utilities::Date::MyDate DateShifterDummy::TenorDate(const Utilities::Date::MyDate &date, const Utilities::Date::MyTenor &tenor) const
        {
            return date.Add(tenor);
        }
    }
}