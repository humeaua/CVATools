//
//  YieldCurve.h
//  FinanceTools
//
//  Created by Alexandre HUMEAU on 04/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Seminaire_YieldCurve_h
#define Seminaire_YieldCurve_h

#include "InterExtrapolation.h"
#include <string>
#include "Date.h"

namespace Finance
{
    namespace Base
    {
        class YieldCurve : public Utilities::Interp::InterExtrapolation1D
        {
        protected:
            std::string cCCY_;
            std::string cName_;
            Utilities::Date::MyDate sToday_;
        public:
            YieldCurve();
            YieldCurve(const Utilities::Date::MyDate & sToday, const std::string & cCCY, const std::string & cName, const std::vector<std::pair<double, double> > & YC);
            
            virtual std::string GetCurrency() const;
            virtual std::string GetName() const;
            
            //  Cash operators : cash rates
            virtual double operator()(double t) const;
            virtual double operator()(const Utilities::Date::MyDate & sToday) const;
            
            //  Forward Operators
            virtual double operator()(double t1, double t2) const;
            virtual double operator()(const Utilities::Date::MyDate & Date1, const Utilities::Date::MyDate & Date2) const;
            
            virtual YieldCurve operator + (const YieldCurve & sYieldCurve);
            virtual YieldCurve operator = (double dValue);
            
            //  the following method apply an exponential shift  - shift * exp(t / tau) on the yield curve
            virtual void ApplyExponentialShift(double dShift, double dTau);
        };
    }
}

#endif
