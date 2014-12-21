//
//  Tour.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 21/12/14.
//
//

#ifndef __CVATools__Tour__
#define __CVATools__Tour__

#include <iostream>

//  Base class for the tours - should be an interface
class Tournament;

class Tour
{
public:
    virtual bool IsFlagShipEvent(const Tournament & tournament) const = 0;
    virtual double MinimumRankingPoints(const Tournament & tournament) const = 0;
};

#endif /* defined(__CVATools__Tour__) */
