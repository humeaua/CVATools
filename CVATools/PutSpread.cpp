//
//  PutSpread.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 28/09/13.
//
//

#include "PutSpread.h"
#include "Require.h"

namespace Finance
{
    namespace Payoff
    {
        PutSpread::PutSpread(double dStrike, double dLeftSpread, double dRightSpread) : dStrike_(dStrike), dLeftSpread_(dLeftSpread), dRightSpread_(dRightSpread)
        {
            REQUIREEXCEPTION(dLeftSpread_ >= 0.0, "Left spread has to be positive");
            REQUIREEXCEPTION(dRightSpread_ >= 0.0, "Right spread has to be positive");
        }
        
        double PutSpread::operator()(const double s1) const
        {
            //  We buy one put of strike dStrike + dRightSpread and sell one put of strike dStrike - dLeftSpread
            return std::max(dStrike_ + dRightSpread_ - s1, 0.0) - std::max(dStrike_ - dLeftSpread_ - s1, 0.0);
        }
        
        BasePayoff1D * PutSpread::clone() const
        {
            return new PutSpread(*this);
        }
    }
}