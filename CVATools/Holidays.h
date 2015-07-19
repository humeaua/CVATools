//
//  Holidays.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 15/07/2015.
//
//

#ifndef __CVATools__Holidays__
#define __CVATools__Holidays__

#include <stdio.h>
#include "IHolidays.h"
#include <set>

namespace Utilities
{
    class Holidays : public IHolidays
    {
    protected:
        std::set<long> m_holidays;
        
    public:
        bool isBusinessDay(const Date::MyDate & date) const;
        
        Holidays * clone() const;
        
        Holidays(const std::set<long> & holidays);
    };
}

#endif /* defined(__CVATools__Holidays__) */
