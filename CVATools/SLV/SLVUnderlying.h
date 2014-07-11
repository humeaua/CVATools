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
    class RateUnderlying;
    class Underlying
    {
        std::tr1::shared_ptr<StochVol> m_StochVol;
        std::tr1::shared_ptr<Finance::Payoff::BasePayoff1D> m_Payoff;
        std::tr1::shared_ptr<RateUnderlying> m_DomesticUnderlying, m_ForeignUnderlying;
    public:
        Underlying(const class StochVol & StochVol,
                   const class Finance::Payoff::BasePayoff1D & BasePayoff,
                   const RateUnderlying & domesticUnderlying,
                   const RateUnderlying & foreignUnderlying);
        
        size_t GetNbFactors() const;
    };
}

#endif /* defined(__CVATools__SLVUnderlying__) */
