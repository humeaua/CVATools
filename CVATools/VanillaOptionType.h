//
//  VanillaOptionType.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 15/02/14.
//
//

#ifndef CVATools_VanillaOptionType_h
#define CVATools_VanillaOptionType_h

namespace Finance
{
    namespace Payoff
    {
        typedef enum
        {
            CALL,
            PUT,
            STRADDLE
        }VanillaOptionType;
    }
}

#endif
