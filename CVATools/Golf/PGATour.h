//
//  PGATour.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 21/12/14.
//
//

#ifndef __CVATools__PGATour__
#define __CVATools__PGATour__

#include <iostream>
#include "MainTour.h"

class PGATour : public MainTour
{
protected:
    double MinimumRankingPointsFlagShipEvent() const;
    double MinimumRankingPointsNormalTournament() const;
public:
    PGATour();
};

#endif /* defined(__CVATools__PGATour__) */
