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
        Digital::Digital(double dStrike, VanillaOptionType eOptionType) : dStrike_(dStrike),  eOptionType_(eOptionType)
        {
            REQUIREEXCEPTION(eOptionType_ == CALL || eOptionType_ == PUT, "Option Type has to be CALL or PUT");
        }
        
        double Digital::pay1(double s1) const
        {
            switch (eOptionType_)
            {
                case CALL:
                {
                    return s1 < dStrike_ ? 0.0 : 1.0;
                }
                case PUT:
                {
                    return s1 < dStrike_ ? 1.0 : 0.0;
                }
                default:
                {
                    throw EXCEPTION("Option type not handled");
                }
            }
            return 0.0;
        }
    }
}