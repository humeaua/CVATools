//
//  RateUnderlying.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 11/07/14.
//
//

#include "RateUnderlying.h"
#include "YieldCurve.h"

namespace SLV
{
    RateUnderlying::RateUnderlying(const Finance::Base::YieldCurve & yieldCurve, bool isDummy) : m_YieldCurve(yieldCurve.clone()), m_IsDummy(isDummy)
    {}
    
    RateUnderlying * RateUnderlying::clone() const
    {
        return new RateUnderlying(*this);
    }
}