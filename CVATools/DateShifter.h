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
#include "Date.h"

namespace Finance
{
    namespace Base
    {
        class DateShifter
        {
            DateShifter(const DateShifter & );
        protected:
            int m_lag;
            Utilities::Date::TimeUnits m_timeUnit;
        public:
            DateShifter(const int & lag, const Utilities::Date::TimeUnits & m_timeUnit);
            virtual Utilities::Date::MyDate Shift(const Utilities::Date::MyDate & input) const;
        };
    }
}

#endif /* defined(__CVATools__DateShifter__) */
