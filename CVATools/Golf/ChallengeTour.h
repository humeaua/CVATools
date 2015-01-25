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
#include "MainTour.h"

class ChallengeTour : public MainTour
{
protected:
    double MinimumRankingPointsFlagShipEvent() const;
    double MinimumRankingPointsNormalTournament() const;
public:
    ChallengeTour();
};

#endif /* defined(__CVATools__ChallengeTour__) */
