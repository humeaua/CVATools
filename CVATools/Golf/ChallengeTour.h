//
//  ChallengeTour.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 12/01/15.
//
//

#ifndef __CVATools__ChallengeTour__
#define __CVATools__ChallengeTour__

#include <iostream>
#include "Tour.h"

class ChallengeTour : public Tour
{
public:
    bool IsFlagShipEvent(const Tournament & tournament) const;
    double MinimumRankingPoints(const Tournament & tournament) const;
};

#endif /* defined(__CVATools__ChallengeTour__) */
