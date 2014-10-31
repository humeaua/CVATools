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
#include <tr1/memory>

namespace Finance
{
    namespace Base
    {
        class IDateShifter;
        typedef std::tr1::shared_ptr<IDateShifter> DateShifter_Ptr;
        
        class Schedule
        {
        protected:
            std::vector<EventOfSchedule> sSchedule_;
            ::Finance::Base::MyFrequency eFrequency_;
            std::vector<double> dCoverage_;
            
        public:
            Schedule(const Utilities::Date::MyDate & sStart, const Utilities::Date::MyDate & sEnd, ::Finance::Base::MyBasis eBasis, ::Finance::Base::MyFrequency eFrequency, const DateShifter_Ptr& fixDS, const DateShifter_Ptr & payDS);
            
            virtual const std::vector<EventOfSchedule> & GetSchedule() const;
            virtual const std::vector<double> & GetCoverage() const;
        };
    }
}

#endif
