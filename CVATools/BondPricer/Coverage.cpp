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
        return GetCoverage(sStart_, sEnd_, eBasis_);
    }
    
    double GetCoverage(const Utilities::Date::MyDate & sStart0, const Utilities::Date::MyDate & sEnd0, MyBasis eBasis)
    {
        double dCoverage = 0.0;
        Utilities::Date::MyDate sStart(sStart0), sEnd(sEnd0);
        long lStart = Utilities::Date::GetDate(sStart), lEnd = Utilities::Date::GetDate(sEnd);
        
        switch (eBasis)
        {
            case BONDBASIS:
            case THIRTY360:
            {
                dCoverage += (sEnd.GetYear() - sStart.GetYear());
                dCoverage += (sEnd.GetMonth() - sStart.GetMonth()) / 12.0;
                if (sEnd.GetDay()== 31 || (sEnd.GetMonth() == 2 && sEnd.GetDay() == 29))
                {
                    sEnd.SetDay(30);
                }
                if (sStart.GetDay() == 31|| (sStart.GetMonth() == 2 && sStart.GetDay() == 29))
                {
                    sStart.SetDay(30);
                }
                dCoverage += (sEnd.GetDay() - sStart.GetDay()) / 360.0;
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
                dCoverage = (lEnd - lStart) / (Utilities::Date::IsLeapYear(sStart.GetYear()) ? 366.0 : 365.0);
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