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

namespace Finance
{
    namespace Base
    {
        EventOfSchedule::EventOfSchedule(const Utilities::Date::MyDate & sStart, const Utilities::Date::MyDate & sEnd, MyBasis eBasis,
                                         const Utilities::Date::MyDate & sFix, const Utilities::Date::MyDate & sPay) :
        
        sStart_(sStart),
        sEnd_(sEnd),
        eBasis_(eBasis),
        sFix_(sFix),
        sPay_(sPay)
        
        {}
        
        EventOfSchedule::EventOfSchedule(const Utilities::Date::MyDate & sStart, const Utilities::Date::MyDate & sEnd, MyBasis eBasis,
                                        const DateShifter_Ptr & fixDS, const DateShifter_Ptr & payDS) :
        sStart_(sStart),
        sEnd_(sEnd),
        eBasis_(eBasis)
        {
            sFix_ = fixDS->GetFixingDate(sStart);
            sPay_ = payDS->GetPaymentDate(sEnd);
        }
        
        double EventOfSchedule::GetCoverage() const
        {
            class Coverage sCoverage(eBasis_,  sStart_, sEnd_);
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