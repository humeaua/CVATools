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
protected:
    double MinimumRankingPointsFlagShipEvent() const;
    double MinimumNormalTournament() const;
public:
    PGATour();
};

#endif /* defined(__CVATools__PGATour__) */
