//
//  Leg.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 21/01/14.
//
//

#ifndef __CVATools__Leg__
#define __CVATools__Leg__

#include <iostream>
#include "Model.h"

namespace Finance
{
    namespace Deal
    {
        class Leg
        {
        public:
            Leg();
            Leg(const Leg & Leg0);
            virtual double Price(const Finance::Models::Model & model, const std::string & reportingCurrency) const = 0;
        };
    }
}

#endif /* defined(__CVATools__Leg__) */
