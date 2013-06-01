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
#include "Require.h"

namespace Finance {
    
    YieldCurve::YieldCurve()
    {
        eInterpolationType_ = Utilities::Interp::RAW;
    }
    
    YieldCurve::YieldCurve(const std::string & cCCY, const std::string & cName, const std::vector<std::pair<double, double> > & YC, Utilities::Interp::InterExtrapolationType eInterExtrapolationType) : 
    
    cCCY_(cCCY),
    cName_(cName)
    
    {
        std::pair<std::vector<double>, std::vector<double> > YC0 = Utilities::GetPairOfVectorFromVectorOfPair(YC);
        dVariables_ = YC0.first;
        dValues_ = YC0.second;
        eInterpolationType_ = eInterExtrapolationType;
    }
    
    YieldCurve::~YieldCurve()
    {}
    
    double YieldCurve::YC(double t) const
    {
        if (t < 1e-03)
        {
            return dValues_[0];
        }
        Utilities::require(t > 0, "t is not positive in YieldCurve::YC");
        return Interp1D(t);
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
        double dTolerance = 0.001;
        YieldCurve sResult;
		
        //  Test if the pillars in the yield curve are equal
        bool bPillarAreEqual = Utilities::AreEqual(sYieldCurve.dVariables_, this->dVariables_, dTolerance);
        Utilities::require(bPillarAreEqual, "Yield curve pillars are not the same. Should be the same for now ");
        
        for (std::size_t iPillar = 0 ; iPillar < sYieldCurve.dVariables_.size() ; ++ iPillar)
        {
            sResult.dVariables_.push_back(sYieldCurve.dVariables_[iPillar] + dVariables_[iPillar]);
            sResult.dValues_.push_back(sYieldCurve.dValues_[iPillar] + dValues_[iPillar]);
        }
        
        return sResult;
    }
    
    YieldCurve YieldCurve::operator=(double dValue)
    {
        eInterpolationType_ = Utilities::Interp::LIN;
        for (std::size_t i = 0 ; i < 31 ; ++i)
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
    
    void YieldCurve::ApplyExponential(double dShift, double dTau)
    {
        for (std::size_t i = 0 ; i < dVariables_.size() ; ++i)
        {
            dValues_[i] -= dShift * exp(-dVariables_[i] / dTau);
        }
    }
}