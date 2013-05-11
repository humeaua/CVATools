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

namespace Finance {
    
    EventOfSchedule::EventOfSchedule(const Utilities::Date::MyDate & sStart, const Utilities::Date::MyDate & sEnd, const YieldCurve & sYieldCurve, MyBasis eBasis) : 
    
    sStart_(sStart),
    sEnd_(sEnd),
    eBasis_(eBasis)
    
    {
        Coverage sCoverage(eBasis_,  sStart_, sEnd);
        dCoverage_ = sCoverage.ComputeCoverage();
        
        //  Assuming that the end date is the pay date
        DF sDiscountFactor(sYieldCurve);
        dPayingDateDF_ = sDiscountFactor.DiscountFactor(sEnd);
    }
    
    EventOfSchedule::~EventOfSchedule()
    {
        sYieldCurve_.~YieldCurve();
        sStart_.~MyDate();
        sEnd_.~MyDate();
    }
    
    double EventOfSchedule::GetCoverage() const
    {
        return dCoverage_;
    }
    
    double EventOfSchedule::GetPayingDateDF() const
    {
        return dPayingDateDF_;
    }
    
    Utilities::Date::MyDate EventOfSchedule::GetEndDate() const
    {
        return sEnd_;
    }
}