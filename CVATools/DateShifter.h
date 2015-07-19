//
//  DateShifter.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 27/10/14.
//
//

#ifndef __CVATools__DateShifter__
#define __CVATools__DateShifter__

#include <iostream>
#include <tr1/memory>
#include "Date.h"
#include "IHolidays.h"

namespace Finance
{
    namespace Base
    {
        class IDateShifter
        {
        public:
            virtual Utilities::Date::MyDate GetSpotDate(const Utilities::Date::MyDate & date) const = 0;
            virtual Utilities::Date::MyDate TenorDate(const Utilities::Date::MyDate & date, const Utilities::Date::MyTenor & tenor) const = 0;
            virtual Utilities::Date::MyDate GetFixingDate(const Utilities::Date::MyDate & date) const = 0;
            virtual Utilities::Date::MyDate GetPaymentDate(const Utilities::Date::MyDate & date) const = 0;
            virtual const Utilities::HolidaysPtr & getHolidays() const = 0;
        };
        
        typedef std::tr1::shared_ptr<IDateShifter> DateShifter_Ptr;
        
        class DateShifterSimple : public IDateShifter
        {
            DateShifterSimple(const DateShifterSimple & );
        protected:
            int m_lag;
            Utilities::Date::TimeUnits m_timeUnit;
            Utilities::HolidaysPtr m_holidays;
        public:
            DateShifterSimple(const int lag, const Utilities::Date::TimeUnits m_timeUnit, const Utilities::HolidaysPtr& holidays);
            Utilities::Date::MyDate GetSpotDate(const Utilities::Date::MyDate & date) const;
            Utilities::Date::MyDate TenorDate(const Utilities::Date::MyDate & date, const Utilities::Date::MyTenor & tenor) const;
            Utilities::Date::MyDate GetFixingDate(const Utilities::Date::MyDate & date) const;
            Utilities::Date::MyDate GetPaymentDate(const Utilities::Date::MyDate & date) const;
            
            const Utilities::HolidaysPtr & getHolidays() const;
        };
    }
}

#endif /* defined(__CVATools__DateShifter__) */
