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
        typedef enum TimeUnits_
        {
            DAY,
            WEEK,
            MONTH,
            YEAR,
            BUSINESSDAY
        }TimeUnits;
        
        std::tm Add(const std::tm &sDate, long lUnit, TimeUnits eTimeUnit);
        
        std::tm GetTime(long lDate);
        long GetDate(const std::tm & sTime);
        bool IsLeapYear(long lYear);
        std::tm CorrectTime(const std::tm& sTime);
        
        class MyDate
        {
        protected:
            int iYear_;
            int iMonth_;
            int iDay_;
        public:
            MyDate();
            MyDate(const int& day, const int& month, const int& year);
            MyDate(const std::tm& sDate);
            MyDate(double dDate);
            MyDate(const MyDate& date);
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
            
            virtual MyDate Add(long iUnit, const TimeUnits& eTimeUnit);
            
            virtual std::string Print() const;
            
            virtual double Diff(const MyDate & sDate) const;
            virtual void SetLocalDate();
            
            virtual std::tm Totm() const;

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
        MyDate InitialiseTodayDate();
    }
}
#endif
