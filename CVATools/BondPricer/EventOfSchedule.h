//
//  EventOfSchedule.h
//  Seminaire
//
//  Created by Alexandre HUMEAU on 23/01/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef Seminaire_EventOfSchedule_h
#define Seminaire_EventOfSchedule_h

#include "Date.h"
#include "Basis.h"
#include "YieldCurve.h"

namespace Finance
{
    class EventOfSchedule
    {
    protected:
        
        //  the pay date is the end date
        Utilities::Date::MyDate sStart_, sEnd_;
        double dCoverage_;
        double dPayingDateDF_;
        
        MyBasis eBasis_;
        
        YieldCurve sYieldCurve_;
        
    public:
        
        EventOfSchedule(const Utilities::Date::MyDate & sStart, const Utilities::Date::MyDate & sEnd, const YieldCurve & sYieldCurve, MyBasis eBasis);
        virtual ~EventOfSchedule();
        
        virtual double GetCoverage() const;
        virtual double GetPayingDateDF() const;
        virtual Utilities::Date::MyDate GetEndDate() const;
    };
}

#endif
