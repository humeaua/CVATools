//
//  DummyRateUnderlying.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 11/07/14.
//
//

#include "DummyRateUnderlying.h"

namespace SLV
{
    DummyUnderlying::DummyUnderlying(const Finance::Base::YieldCurve & yieldCurve) : RateUnderlying(yieldCurve, true)
    {}
    
    RateUnderlying * DummyUnderlying::clone() const
    {
        return new DummyUnderlying(*this);
    }
}