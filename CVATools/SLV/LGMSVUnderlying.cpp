//
//  LGMSVUnderlying.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 11/07/14.
//
//

#include "LGMSVUnderlying.h"

namespace SLV
{
    LGM1FSVUnderlying::LGM1FSVUnderlying(const Finance::Base::YieldCurve & yieldCurve) : RateUnderlying(yieldCurve,false)
    {}
    
    RateUnderlying * LGM1FSVUnderlying::clone() const
    {
        return new LGM1FSVUnderlying(*this);
    }
}