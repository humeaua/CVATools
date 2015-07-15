//
//  IHolidays.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 15/07/2015.
//
//

#ifndef CVATools_IHolidays_h
#define CVATools_IHolidays_h

#include <tr1/memory>

namespace Utilities
{
    namespace Date
    {
        class MyDate;
    }
    struct IHolidays
    {
        virtual bool isBusinessDay(const Date::MyDate & date) const = 0;
        
        virtual IHolidays * clone() const = 0;
        virtual ~IHolidays(){}
    };
    
    typedef std::tr1::shared_ptr<Utilities::IHolidays> HolidaysPtr;
}

#endif
