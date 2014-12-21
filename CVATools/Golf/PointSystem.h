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

class PointSystem
{
public:
    virtual double HomeRatingValue() const = 0;
    virtual double WorldEventRatingValue() const = 0;
};

#endif /* defined(__CVATools__PointSystem__) */
