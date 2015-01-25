//
//  PGATourCanada.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 25/01/15.
//
//

#ifndef __CVATools__PGATourCanada__
#define __CVATools__PGATourCanada__

#include <iostream>
#include "Tour.h"

class PGATourCanada : public Tour
{
protected:
    double MinimumRankingPointsNormalTournament() const;
};

#endif /* defined(__CVATools__PGATourCanada__) */
