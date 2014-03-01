//
//  Leg.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 21/01/14.
//
//

#include "Leg.h"

namespace Finance
{
    namespace Deal
    {
        Leg::Leg()
        {}
        
        Leg::Leg(const Leg & Leg0)
        {
            *this = Leg0;
        }
    }
}