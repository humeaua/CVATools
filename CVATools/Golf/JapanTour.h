//
//  JapanTour.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 17/01/15.
//
//

#ifndef __CVATools__JapanTour__
#define __CVATools__JapanTour__

#include <iostream>
#include "MainTour.h"

class JapanTour : public MainTour
{
protected:
    double MinimumRankingPointsFlagShipEvent() const;
    double MinimumRankingPointsNormalTournament() const;
public:
    JapanTour();
};

#endif /* defined(__CVATools__JapanTour__) */
