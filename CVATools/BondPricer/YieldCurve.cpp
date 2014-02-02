//
//  YieldCurve.cpp
//  MyLibrary
//
//  Created by Alexandre HUMEAU on 30/08/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "YieldCurve.h"
#include "VectorUtilities.h"
#include <stdexcept>

namespace Finance
{
    namespace Base
    {
        YieldCurve::YieldCurve() : Utilities::Interp::LogLinDFInterpolator(std::vector<double>(), std::vector<double>())
        {}
        
        YieldCurve::YieldCurve(const Utilities::Date::MyDate & sToday, const std::string & cCCY, const std::string & cName,const std::pair<std::vector<double>, std::vector<double> > & YC) :
        
        cCCY_(cCCY),
        cName_(cName),
        sToday_(sToday),
        Utilities::Interp::LogLinDFInterpolator(YC.first, YC.second)
        
        {
            //std::pair<std::vector<double>, std::vector<double> > YC0 = Utilities::GetPairOfVectorFromVectorOfPair(YC);
            //dVariables_ = YC0.first;
            //dValues_ = YC0.second;
        }
        
        double YieldCurve::operator()(double t) const
        {
#ifndef EPSILON_YC
#define EPSILON_YC 1e-03
#endif
            if (t < EPSILON_YC)
            {
                return dValues_.at(0);
            }
            if (t > 0)
            {
                return Utilities::Interp::LogLinDFInterpolator::operator()(t);
            }
            else
            {
                throw EXCEPTION("t is not positive");
            }
        }
        
        double YieldCurve::operator()(const Utilities::Date::MyDate & Date) const
        {
            return (*this)(Date.Diff(sToday_));
        }
        
        double YieldCurve::operator()(double t1, double t2) const
        {
            REQUIREEXCEPTION(t1 <= t2, "t1 is after t2");
            REQUIREEXCEPTION(t1 >= 0, "t1 is negative");
            return ((*this)(t2) * t2 -  (*this)(t1) * t1) / (t2 - t1);
        }
        
        double YieldCurve::operator()(const Utilities::Date::MyDate &Date1, const Utilities::Date::MyDate &Date2) const
        {
            REQUIREEXCEPTION(Date1 >= sToday_, "Date1 is before today");
            REQUIREEXCEPTION(Date2 >= Date1, "Date2 is before Date1");
            
            const double t1 = Date1.Diff(sToday_), t2 = Date2.Diff(sToday_);
            return (*this)(t1, t2);
        }
        
        std::string YieldCurve::GetCurrency() const
        {
            return cCCY_;
        }
        
        std::string YieldCurve::GetName() const
        {
            return cName_;
        }
        
        YieldCurve YieldCurve::operator + (const YieldCurve & sYieldCurve)
        {
            const double dTolerance = 0.001;
            YieldCurve sResult;
            
            //  Test if the pillars in the yield curve are equal
            const bool bPillarAreEqual = Utilities::AreEqual(sYieldCurve.dVariables_, this->dVariables_, dTolerance);
            REQUIREEXCEPTION(bPillarAreEqual, "Yield curve pillars are not the same. Should be the same for now");
            
            for (std::size_t iPillar = 0 ; iPillar < sYieldCurve.dVariables_.size() ; ++ iPillar)
            {
                sResult.dVariables_.push_back(sYieldCurve.dVariables_.at(iPillar) + dVariables_.at(iPillar));
                sResult.dValues_.push_back(sYieldCurve.dValues_.at(iPillar) + dValues_.at(iPillar));
            }
            
            return sResult;
        }
        
        YieldCurve YieldCurve::operator=(double dValue)
        {
            //  Clear everything before filling anything
            //eInterpolationType_ = Utilities::Interp::LIN;
            dValues_.clear();
            dVariables_.clear();
            for (std::size_t i = 0 ; i < 2 ; ++i)
            {
                if (i >= dVariables_.size())
                {
                    dVariables_.push_back(i);
                    dValues_.push_back(dValue);
                }
                else
                {
                    dVariables_[i] = i;
                    dValues_[i] = dValue;
                }
            }
            return *this;
        }
        
        void YieldCurve::ApplyExponentialShift(double dShift, double dTau)
        {
            for (std::size_t i = 0 ; i < dVariables_.size() ; ++i)
            {
                dValues_.at(i) -= dShift * exp(-dVariables_.at(i) / dTau);
            }
        }
        
        const Utilities::Date::MyDate& YieldCurve::Today() const
        {
            return sToday_;
        }
    }
}