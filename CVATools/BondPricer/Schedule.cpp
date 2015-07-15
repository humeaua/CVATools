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

namespace Finance
{
    namespace Base
    {
        Schedule::Schedule(const Utilities::Date::MyDate & sStart,
                           const Utilities::Date::MyDate & sEnd,
                           ::Finance::Base::MyBasis eBasis,
                           ::Finance::Base::MyFrequency eFrequency,
                           const DateShifter_Ptr & fixDS,
                           const DateShifter_Ptr & payDS,
                           const Utilities::HolidaysPtr & holidays) : eFrequency_(eFrequency)
        {
            Utilities::Date::MyDate sCurrentStart = sStart;
            std::pair<std::size_t, Utilities::Date::TimeUnits> NumberAndUnitToAdd = ::Finance::Base::Frequency::ParseFrequency(eFrequency_);
            Utilities::Date::MyDate sCurrentEnd = sStart.Add( NumberAndUnitToAdd.first, NumberAndUnitToAdd.second, *holidays);
            
            //  Computation of vector of coverage from today date            
            while (sCurrentEnd <= sEnd)
            {
                EventOfSchedule event(sCurrentStart, sCurrentEnd, eBasis, fixDS, payDS);
                sSchedule_.push_back(event);
                
                // Vect of coverage from today
                dCoverage_.push_back(Coverage(eBasis, sCurrentStart, sCurrentEnd, holidays).ComputeCoverage());
                
                //  Update current
                sCurrentStart = sCurrentEnd;
                sCurrentEnd = sCurrentEnd.Add(NumberAndUnitToAdd.first, NumberAndUnitToAdd.second, *holidays);
            }
        }
        
        const std::vector<EventOfSchedule> & Schedule::GetSchedule() const
        {
            return sSchedule_;
        }
        
        const std::vector<double> & Schedule::GetCoverage() const
        {
            return dCoverage_;
        }
    }
}
