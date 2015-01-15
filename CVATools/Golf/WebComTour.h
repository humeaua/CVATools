//
//  WebComTour.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 15/01/15.
//
//

#ifndef __CVATools__WebComTour__
#define __CVATools__WebComTour__

#include <iostream>
#include "Tour.h"

class WebComTour : public Tour
{
protected:
    double MinimumRankingPointsFlagShipEvent() const;
    double MinimumNormalTournament() const;
public:
    WebComTour();
};

#endif /* defined(__CVATools__WebComTour__) */
