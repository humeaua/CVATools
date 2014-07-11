//
//  LGMUnderlying.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 11/07/14.
//
//

#include "LGMUnderlying.h"

namespace SLV
{
    LGM1FUnderlying::LGM1FUnderlying(const Finance::Base::YieldCurve & yieldCurve) : RateUnderlying(yieldCurve, false)
    {}
    
    RateUnderlying * LGM1FUnderlying::clone() const
    {
        return new LGM1FUnderlying(*this);
    }
}