//
//  Schedule.cpp
//  Seminaire
//
//  Created by Alexandre HUMEAU on 23/01/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Schedule.h"
#include "Coverage.h"

namespace Finance {
    
    Schedule::Schedule(const Utilities::Date::MyDate & sStart, const Utilities::Date::MyDate & sEnd, MyBasis eBasis, MyFrequency eFrequency) : eFrequency_(eFrequency)
    {
        Utilities::Date::MyDate sCurrentStart, sCurrentEnd = sStart;
        std::pair<std::size_t, Utilities::Date::TimeUnits> NumberAndUnitToAdd = Frequency::ParseFrequency(eFrequency_);
        sCurrentStart = sStart;
        sCurrentEnd.Add( NumberAndUnitToAdd.first, NumberAndUnitToAdd.second);
        
        //  Computation of vector of coverage from today date
        
        //  Initialization of Today Date
        std::time_t lToday;
        std::tm *stm;
        time(&lToday);
        
        stm = localtime(&lToday);
        static Utilities::Date::MyDate sTodayDate(*stm);
        sTodayDate.Add(1900, Utilities::Date::YEAR);
        
        while (sCurrentEnd <= sEnd)
        {
            EventOfSchedule sEvent(sCurrentStart, sCurrentEnd, eBasis);
            sSchedule_.push_back(sEvent);
            
            // Vect of coverage from today
            class Coverage sCoverageFromToday(eBasis, sTodayDate, sCurrentEnd);
            dCoverageFromToday_.push_back(sCoverageFromToday.ComputeCoverage());
            
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
    
    std::vector<double> Schedule::GetCoverageFromToday() const
    {
        return dCoverageFromToday_;
    }
}