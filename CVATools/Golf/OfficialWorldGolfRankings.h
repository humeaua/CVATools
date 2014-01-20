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
        static Utilities::Interp::LinearInterpolator GetOWGRDiscountCurve();
        static Utilities::Interp::LinearInterpolator GetTennisDiscountCurve();
    public:
        static Utilities::Interp::LinearInterpolator GetDiscountCurve(DiscountType eDiscountType = GOLF) ;
    };
}

#endif /* defined(__CVATools__OfficialWorldGolfRankings__) */
