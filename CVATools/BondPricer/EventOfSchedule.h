//
//  EventOfSchedule.h
//  Seminaire
//
//  Created by Alexandre HUMEAU on 23/01/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef Seminaire_EventOfSchedule_h
#define Seminaire_EventOfSchedule_h

#include "Date.h"
#include "Basis.h"
#include "YieldCurve.h"
#include <tr1/memory>
#include "IHolidays.h"

namespace Finance
{
    namespace Base
    {
        class IDateShifter;
        typedef std::tr1::shared_ptr<IDateShifter> DateShifter_Ptr;
        class EventOfSchedule
        {
        protected:
            //  the pay date is the end date
            Utilities::Date::MyDate sFix_, sStart_, sEnd_, sPay_;
            
            Finance::Base::MyBasis eBasis_;
            Utilities::HolidaysPtr m_holidays;
        public:
            
            EventOfSchedule(const Utilities::Date::MyDate & sStart, const Utilities::Date::MyDate & sEnd, Finance::Base::MyBasis eBasis,
                            const Utilities::Date::MyDate & sFix, const Utilities::Date::MyDate & sPay);
            
            EventOfSchedule(const Utilities::Date::MyDate & sStart, const Utilities::Date::MyDate & sEnd, Finance::Base::MyBasis eBasis,
                            const DateShifter_Ptr & fixDS, const DateShifter_Ptr & payDS);
            
            virtual double GetCoverage() const;
            virtual double GetPayingDateDF(const Finance::Base::YieldCurve & sYieldCurve) const;
            virtual const Utilities::Date::MyDate & GetEndDate() const;
            virtual const Utilities::Date::MyDate &  GetStartDate() const;
            virtual const Utilities::Date::MyDate &  GetFixingDate() const;
            virtual const Utilities::Date::MyDate &  GetPaymentDate() const;
            virtual ::Finance::Base::MyBasis GetBasis() const;
        };
    }
}

#endif
