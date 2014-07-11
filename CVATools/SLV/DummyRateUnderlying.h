//
//  DummyRateUnderlying.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 11/07/14.
//
//

#ifndef __CVATools__DummyRateUnderlying__
#define __CVATools__DummyRateUnderlying__

#include <iostream>
#include "RateUnderlying.h"

namespace SLV
{
    class DummyUnderlying : public RateUnderlying
    {
    public:
        DummyUnderlying(const Finance::Base::YieldCurve & yieldCurve);
        
        RateUnderlying * clone() const;
    };
}

#endif /* defined(__CVATools__DummyRateUnderlying__) */
