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

namespace Finance
{
    namespace Base
    {
        EventOfSchedule::EventOfSchedule(const Utilities::Date::MyDate & sStart, const Utilities::Date::MyDate & sEnd, MyBasis eBasis) :
        
        sStart_(sStart),
        sEnd_(sEnd),
        eBasis_(eBasis)
        
        {}
        
        EventOfSchedule::~EventOfSchedule()
        {
            sStart_.~MyDate();
            sEnd_.~MyDate();
        }
        
        double EventOfSchedule::GetCoverage() const
        {
            class Coverage sCoverage(eBasis_,  sStart_, sEnd_);
            return sCoverage.ComputeCoverage();
        }
        
        double EventOfSchedule::GetPayingDateDF(const YieldCurve & sYieldCurve) const
        {
            Instruments::DF sDF(sYieldCurve);
            return sDF.DiscountFactor(sEnd_);
        }
        
        Utilities::Date::MyDate EventOfSchedule::GetEndDate() const
        {
            return sEnd_;
        }
        
        Utilities::Date::MyDate EventOfSchedule::GetStartDate() const
        {
            return sStart_;
        }
        
        MyBasis EventOfSchedule::GetBasis() const
        {
            return eBasis_;
        }
    }
}