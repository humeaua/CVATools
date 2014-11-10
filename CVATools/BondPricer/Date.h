//
//  Date.h
//  Seminaire
//
//  Created by Alexandre HUMEAU on 26/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Seminaire_Date_h
#define Seminaire_Date_h

#include <iostream>

namespace Utilities
{    
    namespace Date
    {
        enum TimeUnits
        {
            DAY,
            WEEK,
            MONTH,
            YEAR,
            BUSINESSDAY
        };
        
        std::tm Add(const std::tm &sDate, long lUnit, TimeUnits eTimeUnit);
        
        std::tm GetTime(long lDate);
        long GetDate(const std::tm & sTime);
        bool IsLeapYear(long lYear);
        std::tm CorrectTime(const std::tm& sTime);
        
        class MyTenor;
        
        class MyDate
        {
        protected:
            unsigned int iYear_;
            unsigned int iMonth_;
            unsigned int iDay_;
            unsigned long m_ExcelDate;
        public:
            MyDate(int day, int month, int year);
            MyDate(const std::tm& sDate);
            MyDate(double dDate);
            virtual ~MyDate();
            
            virtual bool IsValid() const;
            virtual bool IsBusinessDay() const;
            virtual bool IsLeapYear() const;
            
            virtual MyDate NextBusinessDay() const;
            virtual MyDate PreviousBusinessDay() const;
            
            virtual bool IsWeekendDay() const;
            
            virtual int GetDay() const ;
            virtual int GetMonth() const ;
            virtual int GetYear() const ;
            
            virtual void SetDay(const int& iDay);
            virtual void SetMonth(const int& iMonth);
            virtual void SetYear(const int& iYear);
            
            virtual MyDate operator ++(); // prefix
            virtual MyDate operator ++(int); // postfix
            virtual MyDate operator --(); // prefix
            virtual MyDate operator --(int); // postfix
            
            //Add must be const, should not alter the original date
            virtual MyDate Add(long iUnit, const TimeUnits& eTimeUnit) const;
            virtual MyDate Add(const MyTenor & tenor) const;
            
            virtual std::string Print() const;
            
            virtual double Diff(const MyDate & sDate) const;
            virtual void SetLocalDate();
            
            virtual std::tm Totm() const;
            virtual long GetDays1900() const;
        };
        
        bool operator == (const MyDate&, const MyDate&); // comparison operators
        bool operator != (const MyDate&, const MyDate&);
        bool operator < (const MyDate&, const MyDate&);
        bool operator > (const MyDate&, const MyDate&);
        bool operator <= (const MyDate&, const MyDate&);
        bool operator >= (const MyDate&, const MyDate&);
        
        MyDate previous_date(const MyDate& d);
        MyDate next_date(const MyDate& d);
        
        long GetDate(const MyDate & sDate);
        
        class MyTenor
        {
            void Parse(const std::string & tenor);
        protected:
            long m_lag;
            TimeUnits m_timeUnit;
        public:
            MyTenor(const std::string & tenor);
            
            const long & GetLag() const;
            const TimeUnits & GetTimeUnit() const;
            long & GetLag();
            TimeUnits & GetTimeUnit();
        };
    }
}
#endif
