//
//  EuropeanTour.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 07/01/15.
//
//

#ifndef __CVATools__EuropeanTour__
#define __CVATools__EuropeanTour__

#include <iostream>
#include "MainTour.h"

class EuropeanTour : public MainTour
{
protected:
    double MinimumRankingPointsFlagShipEvent() const;
    double MinimumRankingPointsNormalTournament() const;
public:
    EuropeanTour();
};

#endif /* defined(__CVATools__EuropeanTour__) */
