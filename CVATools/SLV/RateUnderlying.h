//
//  RateUnderlying.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 11/07/14.
//
//

#ifndef __CVATools__RateUnderlying__
#define __CVATools__RateUnderlying__

#include <iostream>
#include <tr1/memory>

namespace Finance
{
    namespace Base
    {
        class YieldCurve;
    }
}

namespace SLV
{
    class RateUnderlying
    {
        std::tr1::shared_ptr<Finance::Base::YieldCurve> m_YieldCurve;
    public:
        RateUnderlying(const Finance::Base::YieldCurve & m_YieldCurve);
        
        virtual RateUnderlying * clone() const;
    };
}

#endif /* defined(__CVATools__RateUnderlying__) */
