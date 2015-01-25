//
//  SecondaryTour.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 25/01/15.
//
//

#ifndef __CVATools__SecondaryTour__
#define __CVATools__SecondaryTour__

#include <iostream>
#include "Tour.h"

class SecondaryTour : public Tour
{
public:
    double MinimumRankingPoints(const Tournament & tournament) const;
};

#endif /* defined(__CVATools__SecondaryTour__) */
