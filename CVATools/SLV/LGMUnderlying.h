//
//  LGMUnderlying.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 11/07/14.
//
//

#ifndef __CVATools__LGMUnderlying__
#define __CVATools__LGMUnderlying__

#include <iostream>
#include "RateUnderlying.h"
#include "TermStructure.h"

namespace SLV
{
    class LGM1FUnderlying : public RateUnderlying
    {
    public:
        LGM1FUnderlying(const Finance::Base::YieldCurve & yieldCurve);
        
        RateUnderlying * clone() const;
    private:
        Finance::Base::TermStructure<double, double> m_Sigma;
        double m_Lambda;
    };
}

#endif /* defined(__CVATools__LGMUnderlying__) */
