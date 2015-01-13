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
#include "Tour.h"

class EuropeanTour : public Tour
{
protected:
    double MinimumRankingPointsFlagShipEvent() const;
    double MinimumNormalTournament() const;
public:
    EuropeanTour();
};

#endif /* defined(__CVATools__EuropeanTour__) */
