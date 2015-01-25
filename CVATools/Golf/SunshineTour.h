//
//  SunshineTour.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 18/01/15.
//
//

#ifndef __CVATools__SunshineTour__
#define __CVATools__SunshineTour__

#include <iostream>
#include "MainTour.h"

class SunshineTour : public MainTour
{
protected:
    double MinimumRankingPointsFlagShipEvent() const;
    double MinimumRankingPointsNormalTournament() const;
public:
    SunshineTour();
};

#endif /* defined(__CVATools__SunshineTour__) */
