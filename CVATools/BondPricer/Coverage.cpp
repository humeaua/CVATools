//
//  Coverage.cpp
//  Seminaire
//
//  Created by Alexandre HUMEAU on 23/01/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Coverage.h"
//#include <stdexcept>

namespace Finance
{
    namespace Base
    {
        using namespace std;
        Coverage::Coverage(::Finance::Base::MyBasis eBasis, const Utilities::Date::MyDate & lStart, const Utilities::Date::MyDate & lEnd) : eBasis_(eBasis), sStart_(lStart), sEnd_(lEnd)
        {}
        
        Coverage::~Coverage()
        {}
        
        ::Finance::Base::MyBasis Coverage::GetBasis() const
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
        
        double GetCoverage(const Utilities::Date::MyDate & sStart0, const Utilities::Date::MyDate & sEnd0, ::Finance::Base::MyBasis eBasis)
        {
            double dCoverage = 0.0;
            Utilities::Date::MyDate sStart(sStart0), sEnd(sEnd0);
            long lStart = Utilities::Date::GetDate(sStart), lEnd = Utilities::Date::GetDate(sEnd);
            
            switch (eBasis)
            {
                case ::Finance::Base::BONDBASIS:
                case ::Finance::Base::THIRTY360:
                case ::Finance::Base::_BB:
                case ::Finance::Base::_30360:
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
                case ::Finance::Base::MONEYMARKET:
                case ::Finance::Base::ACT360:
                case ::Finance::Base::_A0:
                case ::Finance::Base::_MM:
                {
                    dCoverage = (lEnd - lStart) / 360.0;
                    break;
                }
                case ::Finance::Base::ACT365FIXED:
                {
                    dCoverage = (lEnd - lStart) / 365.0;
                    break;
                }
                case ::Finance::Base::ACT365:
                case ::Finance::Base::_A5:
                {
                    dCoverage = (lEnd - lStart) / (Utilities::Date::IsLeapYear(sStart.GetYear()) ? 366.0 : 365.0);
                    break;
                }
                case ::Finance::Base::ACT364:
                case ::Finance::Base::_A4:
                {
                    dCoverage = (lEnd - lStart) / 364.0;
                    break;
                }
                case ::Finance::Base::BUS252:
                case ::Finance::Base::_B2:
                {
                    long lCount = 0;
                    while (sStart <= sEnd)
                    {
                        if (sStart.IsBusinessDay())
                        {
                            lCount++;
                        }
                        sStart++;
                    }
                    dCoverage = lCount / 252.0;
                    break;
                }
                default:
                    break;
            }
            return dCoverage;
        }
    }
}