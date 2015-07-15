//
//  Holidays.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 15/07/2015.
//
//

#include "Holidays.h"
#include "Date.h"

namespace Utilities
{
    bool Holidays::isBusinessDay(const Utilities::Date::MyDate &date) const
    {
        const long date1900 = date.GetDays1900();
        return m_holidays.find(date1900) != m_holidays.end();
    }
    
    Holidays * Holidays::clone() const
    {
        return new Holidays(*this);
    }
}