//
//  EventOfSchedule.cpp
//  Seminaire
//
//  Created by Alexandre HUMEAU on 23/01/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "EventOfSchedule.h"
#include "Coverage.h"
#include "DiscountFactor.h"
#include "DateShifter.h"
#include "Holidays.h"

#include <utility>

namespace Finance
{
    namespace Base
    {
        EventOfSchedule::EventOfSchedule(const Utilities::Date::MyDate & sStart, const Utilities::Date::MyDate & sEnd, MyBasis eBasis,
                                        const DateShifter_Ptr & dateShifter) :
        sStart_(sStart),
        sEnd_(sEnd),
        eBasis_(eBasis),
        sFix_(dateShifter->GetFixingDate(sStart)),
        sPay_(dateShifter->GetPaymentDate(sEnd)),
        m_holidays(dateShifter->getHolidays())
        {}
        
        EventOfSchedule::EventOfSchedule()
        {
            eBasis_ = NONE;
        }
        
        double EventOfSchedule::GetCoverage() const
        {
            class Coverage sCoverage(eBasis_,  sStart_, sEnd_, *m_holidays);
            return sCoverage.ComputeCoverage();
        }
        
        double EventOfSchedule::GetPayingDateDF(const YieldCurve & sYieldCurve) const
        {
            Instruments::DF sDF(sYieldCurve);
            return sDF(sPay_);
        }
        
        const Utilities::Date::MyDate &  EventOfSchedule::GetEndDate() const
        {
            return sEnd_;
        }
        
        const Utilities::Date::MyDate &  EventOfSchedule::GetStartDate() const
        {
            return sStart_;
        }
        
        const Utilities::Date::MyDate & EventOfSchedule::GetFixingDate() const
        {
            return sFix_;
        }
        
        const Utilities::Date::MyDate & EventOfSchedule::GetPaymentDate() const
        {
            return sPay_;
        }
        
        MyBasis EventOfSchedule::GetBasis() const
        {
            return eBasis_;
        }
    }
}