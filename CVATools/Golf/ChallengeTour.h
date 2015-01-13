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
protected:
    double MinimumRankingPointsFlagShipEvent() const;
    double MinimumNormalTournament() const;
public:
    ChallengeTour();
};

#endif /* defined(__CVATools__ChallengeTour__) */
