//
//  SLVUnderlying.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 11/07/14.
//
//

#include "SLVUnderlying.h"
#include "StochVol.h"
#include "BasePayoff.h"

#include "LGMSVUnderlying.h"
#include "LGMUnderlying.h"

namespace SLV
{
    Underlying::Underlying(const StochVol & stochVol,
                           const Finance::Payoff::BasePayoff1D & basePayoff,
                           const RateUnderlying & domesticUnderlying,
                           const RateUnderlying & foreignUnderlying) : m_StochVol(stochVol.clone()), m_Payoff(basePayoff.clone()), m_DomesticUnderlying(domesticUnderlying.clone()), m_ForeignUnderlying(foreignUnderlying.clone())
    {}
    
    size_t Underlying::GetNbFactors() const
    {
        size_t nFactors = 0;
        if (!m_DomesticUnderlying->IsDummy())
        {
            RateUnderlying * domUnd = m_DomesticUnderlying.get();
            if (dynamic_cast<LGM1FUnderlying*>(domUnd) != NULL)
            {
                nFactors += 1;
            }
            else if (dynamic_cast<LGM1FSVUnderlying*>(domUnd) != NULL)
            {
                nFactors += 2;
            }
        }
        
        if (!m_ForeignUnderlying->IsDummy())
        {
            RateUnderlying * forUnd = m_ForeignUnderlying.get();
            if (dynamic_cast<LGM1FUnderlying*>(forUnd) != NULL)
            {
                nFactors += 1;
            }
            else if (dynamic_cast<LGM1FSVUnderlying*>(forUnd) != NULL)
            {
                nFactors += 2;
            }
        }
        
        return nFactors + 2; // FX + fx stoch vol already in 
    }
}