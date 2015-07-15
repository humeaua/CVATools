//
//  Coverage.h
//  Seminaire
//
//  Created by Alexandre HUMEAU on 23/01/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef Seminaire_Coverage_h
#define Seminaire_Coverage_h

#include "Basis.h"
#include "Date.h"
#include <tr1/memory>

namespace Utilities {
    struct IHolidays;
    
    typedef std::tr1::shared_ptr<Utilities::IHolidays> HolidaysPtr;
}

namespace Finance
{
    namespace Base
    {
        class Coverage
        {
        public:
            Coverage(MyBasis eBasis, const Utilities::Date::MyDate & lStart, const Utilities::Date::MyDate & lEnd, Utilities::HolidaysPtr holidays);
            virtual ~Coverage();
            
            virtual MyBasis GetBasis() const;
            virtual Utilities::Date::MyDate GetStartDate() const;
            virtual Utilities::Date::MyDate GetEndDate() const;
            
            virtual double ComputeCoverage();
        private:
            MyBasis eBasis_;
            
            Utilities::Date::MyDate sStart_, sEnd_;
            Utilities::HolidaysPtr m_holidays;
        };
        
        double GetCoverage(const Utilities::Date::MyDate & lStart, const Utilities::Date::MyDate & lEnd, ::Finance::Base::MyBasis eBasis, const Utilities::IHolidays & holidays);
    }
}

#endif
