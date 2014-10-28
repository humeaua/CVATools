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
                           const DateShifter & fixDS,
                           const DateShifter & payDS) : eFrequency_(eFrequency)
        {
            Utilities::Date::MyDate sCurrentStart, sCurrentEnd = sStart;
            std::pair<std::size_t, Utilities::Date::TimeUnits> NumberAndUnitToAdd = ::Finance::Base::Frequency::ParseFrequency(eFrequency_);
            sCurrentStart = sStart;
            sCurrentEnd.Add( NumberAndUnitToAdd.first, NumberAndUnitToAdd.second);
            
            //  Computation of vector of coverage from today date            
            while (sCurrentEnd <= sEnd)
            {
                sSchedule_.push_back(EventOfSchedule(sCurrentStart, sCurrentEnd, eBasis, fixDS, payDS));
                
                // Vect of coverage from today
                dCoverage_.push_back(Coverage(eBasis, sCurrentStart, sCurrentEnd).ComputeCoverage());
                
                //  Update current
                sCurrentStart = sCurrentEnd;
                sCurrentEnd.Add(NumberAndUnitToAdd.first, NumberAndUnitToAdd.second);
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
