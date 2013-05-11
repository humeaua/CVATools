//
//  Coverage.cpp
//  Seminaire
//
//  Created by Alexandre HUMEAU on 23/01/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Coverage.h"

namespace Finance {
    
    Coverage::Coverage(MyBasis eBasis, const Utilities::Date::MyDate & lStart, const Utilities::Date::MyDate & lEnd) : eBasis_(eBasis), sStart_(lStart), sEnd_(lEnd)
    {}
    
    Coverage::~Coverage()
    {}
    
    MyBasis Coverage::GetBasis() const
    {
        return eBasis_;
    }
    
    Utilities::Date::MyDate Coverage::GetStartDate() const
    {
        return sStart_;
    }
    
    Utilities::Date::MyDate Coverage::GetEndDate() const
    {
        return sEnd_;
    }
    
    double Coverage::ComputeCoverage()
    {
        double dCoverage = 0.0;
        long lStart = Utilities::Date::GetDate(sStart_), lEnd = Utilities::Date::GetDate(sEnd_);
        
        switch (eBasis_) 
        {
            case BONDBASIS:
            case THIRTY360:
            {
                dCoverage += (sEnd_.GetYear() - sStart_.GetYear());
                dCoverage += (sEnd_.GetMonth() - sStart_.GetMonth()) / 12.0;
                if (sEnd_.GetDay()== 31 || (sEnd_.GetMonth() == 2 && sEnd_.GetDay() == 29))
                {
                    sEnd_.SetDay(30);
                }
                if (sStart_.GetDay() == 31|| (sStart_.GetMonth() == 2 && sStart_.GetDay() == 29))
                {
                    sStart_.SetDay(30);
                }
                dCoverage += (sEnd_.GetDay() - sStart_.GetDay()) / 360.0;
                break;
            }    
            case MONEYMARKET:
            case ACT360:
            {
                dCoverage = (lEnd - lStart) / 360.0;
                break;
            }
            case ACT365FIXED:
            {
                dCoverage = (lEnd - lStart) / 365.0;
                break;
            }
            case ACT365:
            {
                dCoverage = (lEnd - lStart) / (Utilities::Date::IsLeapYear(sStart_.GetYear()) ? 366.0 : 365.0);
                break;
            }
            case ACT364:
            {
                dCoverage = (lEnd - lStart) / 364.0;
                break;
            }
            case BUS252:
            {
                break;
            }
            default:
                std::cout << "Coverage : Not yet implemented" << std::endl;
                break;
        }
        return dCoverage;
    }
    
}