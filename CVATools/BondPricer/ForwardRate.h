//
//  ForwardRate.h
//  Seminaire
//
//  Created by Alexandre HUMEAU on 12/12/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Seminaire_ForwardRate_h
#define Seminaire_ForwardRate_h

#include "DiscountFactor.h"

namespace Finance
{
    namespace Instruments
    {
        class ForwardRate
        {
        public:
            ForwardRate(const Base::YieldCurve & sInitialYieldCurve);
            
            virtual double FwdRate(double dStart, double dEnd) const;
            virtual double FwdRate(const Utilities::Date::MyDate & start,
                                   const Utilities::Date::MyDate & end) const;
            virtual const Utilities::Date::MyDate & Today() const;
        private:
            DF m_discountFactor;
        };
    }
}

#endif
