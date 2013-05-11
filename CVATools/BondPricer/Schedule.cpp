//
//  Schedule.cpp
//  Seminaire
//
//  Created by Alexandre HUMEAU on 23/01/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Schedule.h"

namespace Finance {
    
    Schedule::Schedule(const Utilities::Date::MyDate & sStart, const Utilities::Date::MyDate & sEnd, const YieldCurve & sYieldCurve, MyBasis eBasis, MyFrequency eFrequency) : eFrequency_(eFrequency)
    {
        Utilities::Date::MyDate sCurrentStart, sCurrentEnd = sStart;
        std::pair<std::size_t, Utilities::Date::TimeUnits> NumberAndUnitToAdd = Frequency::ParseFrequency(eFrequency_);
        sCurrentStart = sStart;
        sCurrentEnd.Add( NumberAndUnitToAdd.first, NumberAndUnitToAdd.second);
        
        while (sCurrentEnd <= sEnd)
        {
            EventOfSchedule sEvent(sCurrentStart, sCurrentEnd, sYieldCurve, eBasis);
            sSchedule_.push_back(sEvent);
            
            //  Update current
            sCurrentStart = sCurrentEnd;
            sCurrentEnd.Add(NumberAndUnitToAdd.first, NumberAndUnitToAdd.second);
        }
    }
    
    Schedule::~Schedule()
    {
        sSchedule_.clear();
    }
    
    std::vector<EventOfSchedule> Schedule::GetSchedule() const
    {
        return sSchedule_;
    }
}