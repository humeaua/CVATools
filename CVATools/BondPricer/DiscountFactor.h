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
namespace Utilities
{
    namespace Date
    {
        class MyDate;
    }
}

namespace Finance
{
    namespace Instruments
    {
        class DF
        {
        public:
            DF();
            DF(const Base::YieldCurve & sInitialYieldCurve);
            virtual double operator()(double dDate) const;
            virtual double operator()(const Utilities::Date::MyDate & sDate) const;
            virtual const Utilities::Date::MyDate & Today() const;
        private:
            Base::YieldCurve m_initialYieldCurve;
        };
    }
}

#endif