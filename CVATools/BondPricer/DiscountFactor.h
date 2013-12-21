/*
 *  DiscountFactor.h
 *  Seminaire
 *
 *  Created by Emile on 12/12/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef Seminaire_DiscountFactor_h
#define Seminaire_DiscountFactor_h

#include "YieldCurve.h"
#include "Date.h"

namespace Finance
{
    namespace Instruments
    {
        class DF: public Base::YieldCurve
        {
        public:
            DF();
            DF(const YieldCurve & sInitialYieldCurve);
            virtual double operator()(double dDate) const;
            virtual double operator()(const Utilities::Date::MyDate & sDate) const;
        private:	
        };
    }
}

#endif