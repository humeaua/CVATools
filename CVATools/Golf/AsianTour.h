//
//  AsianTour.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 16/01/15.
//
//

#ifndef __CVATools__AsianTour__
#define __CVATools__AsianTour__

#include <iostream>
#include "Tour.h"

class AsianTour : public Tour
{
protected:
    double MinimumRankingPointsFlagShipEvent() const;
    double MinimumNormalTournament() const;
public:
    AsianTour();
};

#endif /* defined(__CVATools__AsianTour__) */
