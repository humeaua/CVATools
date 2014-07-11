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

namespace SLV
{
    Underlying::Underlying(const StochVol & stochVol,
                           const Finance::Payoff::BasePayoff1D & basePayoff) : m_StochVol(stochVol.clone()), m_Payoff(basePayoff.clone())
    {}
}