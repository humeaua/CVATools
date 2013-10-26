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
    typedef enum
    {
        TENNIS,
        GOLF,
        OWGR
    }DiscountType;
    
    class OfficialWorldGolfRankings
    {
    private:
        virtual Utilities::Interp::InterExtrapolation1D GetOWGRDiscountCurve() const;
        virtual Utilities::Interp::InterExtrapolation1D GetTennisDiscountCurve() const;
    public:
        virtual Utilities::Interp::InterExtrapolation1D GetDiscountCurve(DiscountType eDiscountType = GOLF) const;
    };
}

#endif /* defined(__CVATools__OfficialWorldGolfRankings__) */
