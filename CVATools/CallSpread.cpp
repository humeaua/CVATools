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
            Utilities::requireException(dLeftSpread_ >= 0.0, "Left spread has to be positive", "CallSpread::CallSpread");
            Utilities::requireException(dRightSpread_ >= 0.0, "Right spread has to be positive", "CallSpread::CallSpread");
        }
        
        double CallSpread::pay(double s1) const
        {
            //  We buy one call of strike dStrike - dLeftSpread and sell one call of strike dStrike + dRightSpread
            return std::max(s1 - dStrike_ + dLeftSpread_, 0.0) - std::max(s1 - dStrike_ - dRightSpread_, 0.0);
        }
    }
}