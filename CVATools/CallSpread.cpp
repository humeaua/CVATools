//
//  CallSpread.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 28/09/13.
//
//

#include "CallSpread.h"
#include "Require.h"

namespace Finance
{
    namespace Payoff
    {
        CallSpread::CallSpread(double dStrike, double dLeftSpread, double dRightSpread) : dLeftSpread_(dLeftSpread), dStrike_(dStrike), dRightSpread_(dRightSpread)
        {
            REQUIREEXCEPTION(dLeftSpread_ >= 0.0, "Left spread has to be positive");
            REQUIREEXCEPTION(dRightSpread_ >= 0.0, "Right spread has to be positive");
        }
        
        double CallSpread::operator()(double s1) const
        {
            //  We buy one call of strike dStrike - dLeftSpread and sell one call of strike dStrike + dRightSpread
            return std::max(s1 - dStrike_ + dLeftSpread_, 0.0) - std::max(s1 - dStrike_ - dRightSpread_, 0.0);
        }
        
        BasePayoff1D * CallSpread::clone() const
        {
            return new CallSpread(*this);
        }
    }
}