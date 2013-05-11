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

namespace Finance {
    class ForwardRate : public DF
    {
    public:
        ForwardRate();
        ForwardRate(const YieldCurve & sInitialYieldCurve);
        virtual ~ForwardRate();
        
        virtual double FwdRate(double dStart, double dEnd) const;
    };
}

#endif
