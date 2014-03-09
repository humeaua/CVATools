//
//  DeterministicModel.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 08/03/14.
//
//

#ifndef __CVATools__DeterministicModel__
#define __CVATools__DeterministicModel__

#include <iostream>
#include "FXMarket.h"

namespace Finance
{
    namespace Models
    {
        class DeterministicModel : public Finance::Market::FXMarket
        {
        };
    }
}

#endif /* defined(__CVATools__DeterministicModel__) */
