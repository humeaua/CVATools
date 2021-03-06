//
//  Date.cpp
//  Seminaire
//
//  Created by Alexandre HUMEAU on 26/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Date.h"
#include "VectorUtilities.h"
#include <sstream>
#include "Exception.h"
#include "Logger.h"
#include "Holidays.h"

namespace Utilities
{    
    namespace Date
    {
        int DaysAtBeginningOfEachMonth[] = {/*Jan*/0, /*Feb*/31, /*Mar*/59, /*Apr*/90, /*May*/120, /*Jun*/151, /*Jul*/181, /*Aug*/212, /*Sep*/243, /*Oct*/273, /*Nov*/304, /*Dec*/334};
        
        bool MyDate::IsLeapYear() const
        {
            return ((iYear_ % 400 == 0) || ((iYear_ % 4 == 0) && (iYear_ % 100 != 0)));
        }
        
        MyDate::MyDate() : iDay_(0), iMonth_(0), iYear_(0), m_state(INVALID)
        {}
        
        MyDate::MyDate( int day, int month, int year) : iDay_(day), iMonth_(month), iYear_(year), m_state(VALID)
        {
            //  Remove require from constructor as it is throwing an exception
            //Utilities::requireException(IsValid(), "Date is not valid", "MyDate::MyDate");
        }
        
        MyDate::MyDate(const std::tm & sDate) : m_state(VALID)
        {
            iDay_ = sDate.tm_mday;
            iMonth_ = sDate.tm_mon;
            iYear_ = sDate.tm_year;
        }
        
        MyDate::MyDate(const Utilities::Date::MyDate & date) : iDay_(date.GetDay()), iMonth_(date.GetMonth()), iYear_(date.GetYear()), m_state(date.getState())
        {}
        
        int MyDate::GetDay() const
        {
            return iDay_;
        }
        
        int MyDate::GetMonth() const
        {
            return iMonth_;
        }
        
        int MyDate::GetYear() const
        {
            return iYear_;
        }
        
        MyDate::DateState MyDate::getState() const
        {
            return m_state;
        }
        
        void MyDate::ChangeState()
        {
            if (m_state == MyDate::INVALID)
            {
                m_state = VALID;
            }
        }
        
        void MyDate::SetDay(const int& iDay)
        {
            ChangeState();
            iDay_ = iDay;
        }
        
        void MyDate::SetMonth(const int& iMonth)
        {
            ChangeState();
            iMonth_ = iMonth;
        }
        
        void MyDate::SetYear(const int& iYear)
        {
            ChangeState();
            iYear_ = iYear;
        }
        
        bool MyDate::IsWeekendDay() const
        {
            std::tm stm = Totm();
            return (stm.tm_wday == 0 || stm.tm_wday == 6);
        }
        
        bool MyDate::IsBusinessDay(const IHolidays & holidayCalendar) const
        {
            return !IsWeekendDay() || holidayCalendar.isBusinessDay(*this);
        }
        
        MyDate MyDate::NextBusinessDay(const IHolidays & holidayCalendar) const
        {
            MyDate sCopy = *this;
            sCopy++;
            while (!sCopy.IsBusinessDay(holidayCalendar))
            {
                sCopy++;
            }
            return sCopy;
        }
        
        MyDate MyDate::PreviousBusinessDay(const IHolidays & holidayCalendar) const
        {
            MyDate sCopy = *this;
            sCopy--;
            while (!sCopy.IsBusinessDay(holidayCalendar))
            {
                sCopy--;
            }
            return sCopy;
        }
        
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
            if (static_cast<int>(iYear_) < 0)
            {
                return false;
            }
            
            if (iMonth_ > 12 || iMonth_ < 1)
            {
                return false;
            }
            
            if (iDay_ > 31 || iDay_ < 1)
            {
                return false;
            }
            
            if (((iDay_ == 31) && ( (iMonth_ == 2) || (iMonth_ == 4) || (iMonth_ == 6) || (iMonth_ == 9) || (iMonth_ == 11))))
            {
                return false;
            }
            
            if ((iDay_ == 30) && (iMonth_ == 2))
            {
                return false;
            }
            
            // 29th February for leap years
            if (IsLeapYear() && (iDay_ == 29) && (iMonth_ == 2))
            {
                return false;
            }
            
            if (m_state == INVALID)
            {
                return false;
            }
            
            return true;
        }
        
        bool operator == (const MyDate& d1,const MyDate& d2)
        {
            // check for equality
            if (! (d1.IsValid() && (d2.IsValid())) )
            {
                if (!d1.IsValid())
                {
                    throw EXCEPTION("Date 1 is not valid");
                }
                if (!d2.IsValid())
                {
                    throw EXCEPTION("Date 2 is not valid");
                }
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
            }
            
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
                }
            }
            else
            {
                // different year
                return (d1.GetYear()<d2.GetYear());
            }
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
            }
            
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
            
            MyDate ndat=MyDate((d.GetDay()+1),d.GetMonth(),d.GetYear());
            
            // first try adding a day
            if (ndat.IsValid())
            {
                return ndat;
            }
            ndat=MyDate(1,(d.GetMonth()+1),d.GetYear());
            
            // then try adding a month
            if (ndat.IsValid())
            {
                return ndat;
            }
            ndat = MyDate(1,1,(d.GetYear()+1));
            
            // must be next year
            return ndat;
        }
        
        std::string MyDate::ToString(const int ) const
        {
            std::stringstream ss;
            ss << GetDay() << "/" << GetMonth() << "/" << GetYear();
            return ss.str();
        }
        
        MyDate previous_date(const MyDate& d)
        {
            if (!d.IsValid())
            {
                const std::string ss = "Date " + d.ToString() + " is not valid";
                throw EXCEPTION(ss);
            }
            // return the default date
            MyDate pdat = MyDate((d.GetDay() - 1),d.GetMonth(),d.GetYear());
            if (pdat.IsValid())
            {
                return pdat;
            }
            // try same month
            pdat = MyDate(31,(d.GetMonth() - 1),d.GetYear());
            if (pdat.IsValid())
            {
                return pdat;
            }
            // try previous month
            pdat = MyDate(30,(d.GetMonth() - 1),d.GetYear());
            if (pdat.IsValid())
            {
                return pdat;
            }
            pdat = MyDate(29,(d.GetMonth() - 1),d.GetYear());
            if (pdat.IsValid())
            {
                return pdat;
            }
            pdat = MyDate(28,(d.GetMonth() - 1),d.GetYear());
            if (pdat.IsValid())
            {
                return pdat;
            }
            pdat = MyDate(31,12,(d.GetYear() - 1));
            // try previous year
            return pdat;
        }
        
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
        }
        
        double MyDate::Diff(const MyDate & sDate) const
        {
            //  Bond Basis Convention (30/360)
            //return iYear_ - sDate.GetYear() + (iMonth_ - sDate.GetMonth()) / 12.0 + (iDay_ - sDate.GetDay()) / 360.0;
            //  ACT365 convention
            long lFuture = sDate.GetDays1900(), lToday = this->GetDays1900();
            return static_cast<double>(lToday - lFuture) / 365.0;
        }
        
        MyDate MyDate::Add(long iUnit, const TimeUnits& eTimeUnit, const IHolidays & holidays) const
        {
            int iDay;
            MyDate copy = *this;
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
                            copy = next_date(copy);
                        }
                    }
                    else
                    {
                        for (iDay = 0 ; iDay > iUnit ; --iDay)
                        {
                            copy = previous_date(copy);
                        }
                    }
                    break;
                    
                case MONTH:
                    copy.iMonth_ += iUnit;
                    if (iMonth_ > 0)
                    {
                        while (iMonth_ > 11) {
                            copy.iMonth_ -= 12;
                            copy.iYear_ ++;
                        }
                    }
                    else
                    {
                        while (static_cast<int>(iMonth_) < 0) {
                            copy.iMonth_ += 12;
                            copy.iYear_ --;
                        }
                    }
                    break;
                    
                case YEAR:
                    copy.iYear_ += iUnit;
                    if (static_cast<int>(iYear_) < 0)
                    {
                        throw EXCEPTION("Year cannot be negative");
                    }
                    break;
                    
                case BUSINESSDAY:
                    if (iUnit > 0)
                    {
                        for (std::size_t i = 0 ; i < iUnit ; ++i)
                        {
                            copy = copy.NextBusinessDay(holidays);
                        }
                    }
                    else if (iUnit < 0)
                    {
                        for (std::size_t i = 0 ; i > iUnit ; --i)
                        {
                            copy = copy.PreviousBusinessDay(holidays);
                        }
                    }
                    break;
                default:
                    throw EXCEPTION("Could not interpret unit");
                    break;
            }
            return copy;
        }
        
        MyDate MyDate::Add(const Utilities::Date::MyTenor &tenor, const IHolidays & holidays) const
        {
            MyDate copy = Add(tenor.GetLag(), tenor.GetTimeUnit(), holidays);
            return copy;
        }
        
        MyDate::~MyDate()
        {}
        
        long MyDate::GetDays1900() const
        {
            return GetDate(*this);
        }
        
        bool IsLeapYear(long lYear)
        {
            return ((lYear % 400 == 0) || ((lYear % 4 == 0) && (lYear % 100 != 0)));
        }
        
        long GetDate(const MyDate & sDate)
        {
            if (!sDate.IsValid())
            {
                throw EXCEPTION("Date is not valid");
            }
            else
            {
                long lResult = 1;
                int i;
                for (i = 0 ; i < sDate.GetYear() - 1900 ; ++ i)
                {
                    lResult += IsLeapYear(i + 1900) ? 366 : 365;
                }
                lResult += DaysAtBeginningOfEachMonth[sDate.GetMonth() - 1];
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
            return GetDate(MyDate(stime));
        }
        
        //  Does not seem to work at first sight
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
                {
                    iMonth++;
                }
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
        
        std::tm MyDate::Totm() const
        {
            std::tm sDateToBeReturned;
            sDateToBeReturned.tm_mday   = GetDay();
            sDateToBeReturned.tm_mon    = GetMonth();
            sDateToBeReturned.tm_year   = GetYear();
            
            sDateToBeReturned.tm_min    = 0;
            sDateToBeReturned.tm_sec    = 0;
            sDateToBeReturned.tm_hour   = 0;
            sDateToBeReturned.tm_wday   = (GetDate(sDateToBeReturned) - 1) % 7;
            return sDateToBeReturned;
        }
        
        /*std::tm Add(const std::tm& sDate, long lUnit, TimeUnits eTimeUnit)
        {
            MyDate sMyDate(sDate);
            
            sMyDate.Add(lUnit, eTimeUnit);
            
            return sMyDate.Totm();
        }*/
        
        MyTenor::MyTenor(const std::string & tenor)
        {
            Parse(tenor);
        }
        
        MyTenor::MyTenor(const long & lag, const TimeUnits & timeUnit) : m_lag(lag), m_timeUnit(timeUnit)
        {}
        
        void MyTenor::Parse(const std::string &tenor)
        {
            throw EXCEPTION("Not yet implemented");
        }
        
        const long & MyTenor::GetLag() const
        {
            return m_lag;
        }
        
        const TimeUnits & MyTenor::GetTimeUnit() const
        {
            return m_timeUnit;
        }
        
        long & MyTenor::GetLag()
        {
            return m_lag;
        }
        
        TimeUnits & MyTenor::GetTimeUnit()
        {
            return m_timeUnit;
        }
    }
}

template<>
void Utilities::Logger::PutLine(const Utilities::Date::MyDate & date)
{
    m_os << date.GetDay() << "/" << date.GetMonth() << "/" << date.GetYear() << std::endl;
}

Utilities::Logger & operator<<(Utilities::Logger & os, const Utilities::Date::MyDate & date)
{
    os.PutLine(date);
    return os;
}
