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
public:
    bool IsFlagShipEvent(const Tournament & tournament) const;
    double MinimumRankingPoints(const Tournament & tournament) const;
};

#endif /* defined(__CVATools__EuropeanTour__) */
