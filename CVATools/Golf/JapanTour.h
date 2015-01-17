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
#include "Tour.h"

class JapanTour : public Tour
{
protected:
    double MinimumRankingPointsFlagShipEvent() const;
    double MinimumNormalTournament() const;
public:
    JapanTour();
};

#endif /* defined(__CVATools__JapanTour__) */
