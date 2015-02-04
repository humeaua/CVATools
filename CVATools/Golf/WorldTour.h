//
//  WorldTour.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 04/02/15.
//
//

#ifndef __CVATools__WorldTour__
#define __CVATools__WorldTour__

#include <iostream>
#include "Tour.h"

class WorldTour : public Tour
{
protected:
    //  Put 2 methods with the same name since I need the name of tournament for Majors and WGC
    virtual double MinimumRankingPointsNormalTournament() const;
    virtual double MinimumRankingPointsNormalTournament(const Tournament & tournament) const = 0;
public:
    virtual double MinimumRankingPoints(const Tournament & tournament) const;
};

#endif /* defined(__CVATools__WorldTour__) */
