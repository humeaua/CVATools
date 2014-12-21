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
#include "Tour.h"

class PGATour : public Tour
{
public:
    bool IsFlagShipEvent(const Tournament & tournament) const;
    double MinimumRankingPoints(const Tournament & tournament) const;
};

#endif /* defined(__CVATools__PGATour__) */
