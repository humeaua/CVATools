//
//  Date.cpp
//  Seminaire
//
//  Created by Alexandre HUMEAU on 26/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Date.h"

namespace Utilities {
    
    namespace Date {
        
        MyDate::MyDate()
        {
            SetLocalDate();
        }
        
        MyDate::MyDate(double dDate)
        {
            SetLocalDate();
            //  Bond Basis (30/360) convention
            int iYear = (int)dDate, iMonth = (int)((dDate - iYear) * 12), iDay = (int)((dDate - iYear - (double)iMonth / 12) * 30);
            iYear_ += iYear;
            iMonth_ += iMonth;
            iDay_ += iDay;
        }
        
        bool MyDate::IsLeapYear() const
        {
            return ((iYear_ % 400 == 0) || ((iYear_ % 4 == 0) && (iYear_ % 100 != 0)));
        }
        
        MyDate::MyDate(const int& day, const int& month, const int& year)
        {
            static int length[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
            
            iMonth_ = std::max(1, month);
            iMonth_ = std::min(month,12);
            
            iYear_ = std::max(1, year);
            
            if (IsLeapYear() && iMonth_ == 2)
            {
                iDay_ = std::max(1,day);
                iDay_ = std::min(iDay_, length[iMonth_] + 1);
            }
            else
            {
                iDay_ = std::max(1,day);
                iDay_ = std::min(iDay_, length[iMonth_]);
            }
        }
        
        MyDate::MyDate(const std::tm & sDate)
        {
            iDay_ = sDate.tm_mday;
            iMonth_ = sDate.tm_mon;
            iYear_ = sDate.tm_year;
        }
        
        int MyDate::GetDay() const
        {
            return iDay_;
        };
        
        int MyDate::GetMonth() const
        {
            return iMonth_;
        };
        
        int MyDate::GetYear() const
        {
            return iYear_;
        };
        
        void MyDate::SetDay(const int& iDay)
        {
            iDay_ = iDay;
        };
        
        void MyDate::SetMonth(const int& iMonth)
        {
            iMonth_ = iMonth;
        };
        
        void MyDate::SetYear(const int& iYear)
        {
            iYear_ = iYear;
        };
        
        void MyDate::SetLocalDate()
        {
            struct tm *ptr;     
            time_t sec;         
            time(&sec);         
            ptr = localtime(&sec); 
            
            iMonth_ = ptr->tm_mon + 1;
            iDay_   = ptr->tm_mday;
            iYear_  = ptr->tm_year + 1900;
        }
        
        bool MyDate::IsValid() const
        {
            // This function will check the given date is valid or not.
            // If the date is not valid then it will return the value false.
            // Need some more checks on the year, though
            
            if (iYear_ < 0)
                return false;
            
            if (iMonth_ > 12 || iMonth_ < 1)
                return false;
            
            if (iDay_ > 31 || iDay_ < 1)
                return false;
            
            if (((iDay_ == 31) && ( (iMonth_ == 2) || (iMonth_ == 4) || (iMonth_ == 6) || (iMonth_ == 9) || (iMonth_ == 11))))
                return false;
            
            if ((iDay_ == 30) && (iMonth_ == 2))
                return false;
            
            // 29th February for leap years
            if ((iYear_ % 4 != 0)  && (iDay_ == 29) && (iMonth_ == 2))
                return false;
            
            if ((iYear_ % 400 != 0) && (iYear_ % 100 == 0) && (iDay_ == 29) && (iMonth_ == 2))
                return false;
            
            return true;
        };
        
        bool operator == (const MyDate& d1,const MyDate& d2)
        {
            // check for equality
            if (! (d1.IsValid() && (d2.IsValid())) )
            {
                return false;
            }
            
            // if dates not valid, not clear what to do.
            //alternative: throw exception
            return ((d1.GetDay()==d2.GetDay()) && (d1.GetMonth()==d2.GetMonth()) && (d1.GetYear()==d2.GetYear()));
        }
        
        bool operator < (const MyDate& d1, const MyDate& d2)
        {
            if (! (d1.IsValid() && (d2.IsValid())) )
            {
                return false;
            };
            
            if (d1.GetYear()==d2.GetYear())
            {
                // same year
                if (d1.GetMonth()==d2.GetMonth())
                {
                    // same month
                    return (d1.GetDay()<d2.GetDay());
                }
                else
                {
                    return (d1.GetMonth()<d2.GetMonth());
                };
            }
            else
            {
                // different year
                return (d1.GetYear()<d2.GetYear());
            };
        }
        
        // remaining operators dened in terms of the above
        bool operator <=(const MyDate& d1, const MyDate& d2)
        {
            if (d1==d2)
            {
                return true;
            }
            return (d1<d2);
        }
        
        bool operator >=(const MyDate& d1, const MyDate& d2)
        {
            if (d1==d2)
            {
                return true;
            };
            
            return (d1>d2);
        }
        
        bool operator > (const MyDate& d1, const MyDate& d2)
        {
            return !(d1<=d2);
        }
        
        bool operator !=(const MyDate& d1, const MyDate& d2)
        {
            return !(d1==d2);
        }
        
        
        MyDate next_date(const MyDate& d)
        {
            if (!d.IsValid())
            {
                return MyDate(0,0,0);
            }
            
            //
            MyDate ndat=MyDate((d.GetDay()+1),d.GetMonth(),d.GetYear());
            
            // first try adding a day
            if (ndat.IsValid())
                return ndat;
            ndat=MyDate(1,(d.GetMonth()+1),d.GetYear());
            
            // then try adding a month
            if (ndat.IsValid())
                return ndat;
            ndat = MyDate(1,1,(d.GetYear()+1));
            
            // must be next year
            return ndat;
        };
        
        MyDate previous_date(const MyDate& d){
            if (!d.IsValid())
            {
                return MyDate();
            };
            // return the default date
            MyDate pdat = MyDate((d.GetDay() - 1),d.GetMonth(),d.GetYear());
            if (pdat.IsValid())
                return pdat;
            // try same month
            pdat = MyDate(31,(d.GetMonth() - 1),d.GetYear());
            if (pdat.IsValid())
                return pdat;
            // try previous month
            pdat = MyDate(30,(d.GetMonth() - 1),d.GetYear());
            if (pdat.IsValid())
                return pdat;
            pdat = MyDate(29,(d.GetMonth() - 1),d.GetYear());
            if (pdat.IsValid())
                return pdat;
            pdat = MyDate(28,(d.GetMonth() - 1),d.GetYear());
            if (pdat.IsValid())
                return pdat;
            pdat = MyDate(31,12,(d.GetYear() - 1));
            // try previous year
            return pdat;
        };
        
        MyDate MyDate::operator ++(int)
        {
            // postfix operator
            MyDate d = *this;
            *this = next_date(d);
            return d;
        }
        
        MyDate MyDate::operator ++()
        {
            // prefix operator
            *this = next_date(*this);
            return *this;
        }
        
        MyDate MyDate::operator --(int)
        {
            // postfix operator, return current value
            MyDate d = *this;
            *this = previous_date(*this);
            return d;
        }
        
        MyDate MyDate::operator --()
        {
            // prefix operator, return new value
            *this = previous_date(*this);
            return *this;
        };
        
        bool IsLeapYear(const long lYear)
        {
            return ((lYear % 400 == 0) || ((lYear % 4 == 0) && (lYear % 100 != 0)));
        }
        
        double MyDate::Diff(const MyDate & sDate) const
        {
            //  Bond Basis Convention (30/360)
            return iYear_ - sDate.GetYear() + (iMonth_ - sDate.GetMonth()) / 12.0 + (iDay_ - sDate.GetDay()) / 30.0;
        }
        
        void MyDate::Add(long iUnit, const TimeUnits eTimeUnit)
        {
            int iDay;
            if (eTimeUnit == WEEK)
            {
                iUnit *= 7;
            }
            switch (eTimeUnit) {
                case DAY:
                case WEEK:
                    if (iUnit > 0)
                    {
                        for (iDay = 0; iDay < iUnit ; ++iDay)
                        {
                        
                            *this = next_date(*this);
                        }
                    }
                    else
                    {
                        for (iDay = 0 ; iDay > iUnit ; --iDay)
                        {
                            *this = previous_date(*this);
                        }
                    }
                    break;
                    
                case MONTH:
                    iMonth_ += iUnit;
                    if (iMonth_ > 0)
                    {
                        while (iMonth_ > 11) {
                            iMonth_ -= 12;
                            iYear_ ++;
                        }
                    }
                    else
                    {
                        while (iMonth_ < 0) {
                            iMonth_ += 12;
                            iYear_ --;
                        }
                    }
                    break;
                    
                case YEAR:
                    iYear_ += iUnit;
                    if (iYear_ < 0)
                    {
                        //throw MyException((Err)"Year is negative : cannot be negative");
                        std::cout << "MyDate::Add : Year cannot be negative"<< std::endl;
                    }
                    break;
                    
                case BUSINESSDAY:
                default:
                    //throw MyException((Err)"Error in Adding Date : Not yet implemented");
                    std::cout << "MyDate::Add : Not yet implemented (Add Business Day)" << std::endl;
                    break;
            }
        }
        
        MyDate::~MyDate()
        {}
        
        void MyDate::Print() const
        {
            std::cout << "Date : " << iDay_ << "/" << iMonth_ + 1 << "/" << iYear_ + 1900 << std::endl;
        }
        
        int DaysAtBeginningOfEachMonth[] = {/*Jan*/0, /*Feb*/31, /*Mar*/59, /*Apr*/90, /*May*/120, /*Jun*/151, /*Jul*/181, /*Aug*/212, /*Sep*/243, /*Oct*/273, /*Nov*/304, /*Dec*/334};
        
        long GetDate(const MyDate & sDate)
        {
            if (!sDate.IsValid())
            {
                return -1;
            }
            else
            {
                long lResult = 1;
                int i;
                for (i = 0 ; i < sDate.GetYear() ; ++ i)
                {
                    lResult += IsLeapYear(i) ? 366 : 365;
                }
                lResult += DaysAtBeginningOfEachMonth[sDate.GetMonth()];
                if (IsLeapYear(sDate.GetYear()) && sDate.GetMonth() > 2)
                {
                    lResult++;
                }
                lResult += sDate.GetDay();
                
                return lResult;
            }
        }
        
        long GetDate(const tm & stime)
        {
            MyDate sDate(stime);
            return GetDate(sDate);
        }
        
        std::tm GetTime(long lDate)
        {
            tm stime;
            long iDaysRemaining = lDate % 365, iYear = lDate / 365;
            int iMonth = -1, iDays;
            if (iDaysRemaining < iYear / 4)
            {
                iYear--;
                iDaysRemaining += 365;
                iDaysRemaining -= iYear / 4;
            }
            for (int i = 0 ; i < 12 ; ++i)
            {
                if (iDaysRemaining < DaysAtBeginningOfEachMonth[i])
                    iMonth++;
            }
            iDays = static_cast<int>(iDaysRemaining) - DaysAtBeginningOfEachMonth[iMonth - 1];
            
            stime.tm_mday   = iDays;
            stime.tm_mon    = iMonth;
            stime.tm_year   = static_cast<int>(iYear);
            
            stime.tm_min    = 0;
            stime.tm_sec    = 0;
            stime.tm_hour   = 0;
            
            return stime;
        }
        
        tm CorrectTime(const tm& sTime);
        tm CorrectTime(const tm& sTime)
        {
            tm sTime0 = sTime;
            if (sTime0.tm_wday > 7)
            {
                sTime0.tm_wday = sTime0.tm_wday % 7;
            }
            while (sTime0.tm_mon > 12)
            {
                
            }
            return sTime0;
        }
        
        std::tm Add(const std::tm& sDate, long lUnit, TimeUnits eTimeUnit)
        {
            MyDate sMyDate(sDate);
            
            sMyDate.Add(lUnit, eTimeUnit);
            
            std::tm sDateToBeReturned;
            sDateToBeReturned.tm_mday   = sMyDate.GetDay();
            sDateToBeReturned.tm_mon    = sMyDate.GetMonth();
            sDateToBeReturned.tm_year   = sMyDate.GetYear();
            
            sDateToBeReturned.tm_min    = 0;
            sDateToBeReturned.tm_sec    = 0;
            sDateToBeReturned.tm_hour   = 0;
            
            return sDateToBeReturned;
        }
    }
}
