//
//  SLVUnderlying.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 11/07/14.
//
//

#ifndef __CVATools__SLVUnderlying__
#define __CVATools__SLVUnderlying__

#include <iostream>
#include <tr1/memory>

namespace Finance
{
    namespace Payoff
    {
        class BasePayoff1D;
    }
}

namespace SLV
{
    class StochVol;
    class Underlying
    {
        std::tr1::shared_ptr<StochVol> m_StochVol;
        std::tr1::shared_ptr<Finance::Payoff::BasePayoff1D> m_Payoff;
        
    public:
        Underlying(const class StochVol & StochVol, const class Finance::Payoff::BasePayoff1D & BasePayoff);
    };
}

#endif /* defined(__CVATools__SLVUnderlying__) */
