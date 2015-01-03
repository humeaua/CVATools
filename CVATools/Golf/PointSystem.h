//
//  PointSystem.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 21/12/14.
//
//

#ifndef __CVATools__PointSystem__
#define __CVATools__PointSystem__

#include <iostream>

class Tournament;

class PointSystem
{
protected:
    virtual double HomeRatingValue(const Tournament & tournament) const = 0;
    virtual double WorldEventRatingValue(const Tournament & tournament) const = 0;
    
public:
    virtual double TotalRatingValue(const Tournament & tournament) const
    {
        return HomeRatingValue(tournament) + WorldEventRatingValue(tournament);
    }
};

#endif /* defined(__CVATools__PointSystem__) */
