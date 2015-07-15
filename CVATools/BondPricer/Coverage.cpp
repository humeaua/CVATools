//
//  Coverage.cpp
//  Seminaire
//
//  Created by Alexandre HUMEAU on 23/01/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Coverage.h"
#include "Exception.h"

namespace Finance
{
    namespace Base
    {
        Coverage::Coverage(MyBasis eBasis, const Utilities::Date::MyDate & lStart, const Utilities::Date::MyDate & lEnd, Utilities::HolidaysPtr holidays) : eBasis_(eBasis), sStart_(lStart), sEnd_(lEnd), m_holidays(holidays)
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
            return GetCoverage(sStart_, sEnd_, eBasis_, *m_holidays);
        }
        
        double GetCoverage(const Utilities::Date::MyDate & sStart0, const Utilities::Date::MyDate & sEnd0, ::Finance::Base::MyBasis eBasis, const Utilities::IHolidays & holidays)
        {
            double dCoverage = 0.0;
            Utilities::Date::MyDate sStart(sStart0), sEnd(sEnd0);
            
            switch (eBasis)
            {
                case BONDBASIS:
                case THIRTY360:
                case _BB:
                case _30360:
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
                case _A0:
                case _MM:
                {
                    const long lStart = Utilities::Date::GetDate(sStart), lEnd = Utilities::Date::GetDate(sEnd);
                    dCoverage = (lEnd - lStart) / 360.0;
                    break;
                }
                case ACT365FIXED:
                {
                    const long lStart = Utilities::Date::GetDate(sStart), lEnd = Utilities::Date::GetDate(sEnd);
                    
                    dCoverage = (lEnd - lStart) / 365.0;
                    break;
                }
                case ACT365:
                case _A5:
                {
                    const long lStart = Utilities::Date::GetDate(sStart), lEnd = Utilities::Date::GetDate(sEnd);
                    
                    dCoverage = (lEnd - lStart) / (sStart.IsLeapYear() ? 366.0 : 365.0);
                    break;
                }
                case ACT364:
                case _A4:
                {
                    const long lStart = Utilities::Date::GetDate(sStart), lEnd = Utilities::Date::GetDate(sEnd);
                    
                    dCoverage = (lEnd - lStart) / 364.0;
                    break;
                }
                case BUS252:
                case _B2:
                {
                    long lCount = 0;
                    while (sStart <= sEnd)
                    {
                        if (sStart.IsBusinessDay(holidays))
                        {
                            lCount++;
                        }
                        sStart++;
                    }
                    dCoverage = lCount / 252.0;
                    break;
                }
                case NONE:
                case UNITARY:
                {
                    //  return 1
                    return 1;
                }
                default:
                {
                    throw EXCEPTION("Basis not understood");
                    break;
                }
            }
            return dCoverage;
        }
    }
}