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

namespace Finance {
    
    class Coverage
    {
    public:
        Coverage(MyBasis eBasis, const Utilities::Date::MyDate & lStart, const Utilities::Date::MyDate & lEnd);
        virtual ~Coverage();
        
        virtual MyBasis GetBasis() const;
        virtual Utilities::Date::MyDate GetStartDate() const;
        virtual Utilities::Date::MyDate GetEndDate() const;
        
        virtual double ComputeCoverage();
    private:
        MyBasis eBasis_;
        
        Utilities::Date::MyDate sStart_, sEnd_;
        
    };
    
}

#endif
