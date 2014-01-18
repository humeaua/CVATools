//
//  Digital.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 28/09/13.
//
//

#include "Digital.h"
#include "Require.h"

namespace Finance
{
    namespace Payoff
    {
        Digital::Digital(double dStrike, double dLeftSpread, double dRightSpread, VanillaOptionType eOptionType) : dStrike_(dStrike), dLeftSpread_(dLeftSpread), dRightSpread_(dRightSpread), eOptionType_(eOptionType)
        {
            REQUIREEXCEPTION(dLeftSpread_ >= 0.0, "Left spread has to be positive");
            REQUIREEXCEPTION(dRightSpread_ >= 0.0, "Right spread has to be positive");
            REQUIREEXCEPTION(eOptionType_ == CALL || eOptionType_ == PUT, "Option Type has to be CALL or PUT");
        }
        
        double Digital::pay(double s1) const
        {
            switch (eOptionType_)
            {
                case CALL:
                    return s1 < dStrike_ - dLeftSpread_ ? 0.0 : s1 > dStrike_ + dRightSpread_ ? 1.0 : (s1 - dStrike_ + dLeftSpread_) / (dRightSpread_ + dLeftSpread_);
                    break;
                case PUT:
                    return s1 < dStrike_ - dLeftSpread_ ? 1.0 : s1 > dStrike_ + dRightSpread_ ? 0.0 : (dStrike_ - dLeftSpread_ - s1) / (dRightSpread_ + dLeftSpread_);
                    break;
                case STRADDLE:
                default:
                    throw EXCEPTION("Option type not handled");
                    break;
            }
            return 0.0;
        }
    }
}