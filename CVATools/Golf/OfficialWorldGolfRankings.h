//
//  OfficialWorldGolfRankings.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 13/10/13.
//
//

#ifndef __CVATools__OfficialWorldGolfRankings__
#define __CVATools__OfficialWorldGolfRankings__

#include <iostream>
#include "InterExtrapolation.h"

namespace Golf {
    class OfficialWorldGolfRankings
    {
    public:
        virtual Utilities::Interp::InterExtrapolation1D GetOWGRDiscountCurve() const;
        virtual Utilities::Interp::InterExtrapolation1D GetTennisDiscountCurve() const;
    };
}

#endif /* defined(__CVATools__OfficialWorldGolfRankings__) */
