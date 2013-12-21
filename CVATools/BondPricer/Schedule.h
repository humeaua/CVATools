//
//  Schedule.h
//  Seminaire
//
//  Created by Alexandre HUMEAU on 23/01/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef Seminaire_Schedule_h
#define Seminaire_Schedule_h

#include "Date.h"
#include "YieldCurve.h"
#include "Frequency.h"
#include "EventOfSchedule.h"

namespace Finance
{
    namespace Base
    {
        class Schedule
        {
        protected:
            std::vector<EventOfSchedule> sSchedule_;
            ::Finance::Base::MyFrequency eFrequency_;
            std::vector<double> dCoverageFromToday_;
            
        public:
            Schedule(const Utilities::Date::MyDate & sStart, const Utilities::Date::MyDate & sEnd, ::Finance::Base::MyBasis eBasis, ::Finance::Base::MyFrequency eFrequency);
            
            virtual std::vector<EventOfSchedule> GetSchedule() const;
            virtual std::vector<double> GetCoverageFromToday() const;
        };
    }
}

#endif
