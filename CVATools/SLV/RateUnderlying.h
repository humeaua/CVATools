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
        bool m_IsDummy;
    public:
        RateUnderlying(const Finance::Base::YieldCurve & m_YieldCurve, bool isDummy);
        
        virtual RateUnderlying * clone() const;
        
        virtual bool IsDummy() const
        {
            return m_IsDummy;
        }
    };
}

#endif /* defined(__CVATools__RateUnderlying__) */
