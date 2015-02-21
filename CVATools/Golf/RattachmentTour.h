//
//  RattachmentTour.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 08/02/15.
//
//

#ifndef __CVATools__RattachmentTour__
#define __CVATools__RattachmentTour__

#include <iostream>
#include "Tour.h"

//  Class that describes the tour on which the player is rattached
class TourMembership
{
private:
    void Check() const;
    void Reset();
protected:
    TourType m_tourType;
    Tour_ptr m_tour;
public:
    TourMembership(const TourType & tourType);
    
};

#endif /* defined(__CVATools__RattachmentTour__) */
