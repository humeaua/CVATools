//
//  MainTour.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 25/01/15.
//
//

#ifndef __CVATools__MainTour__
#define __CVATools__MainTour__

#include <iostream>
#include "Tour.h"

class MainTour : public Tour
{
protected:
    std::string m_flagshipEventName;
    
    virtual double MinimumRankingPointsFlagShipEvent() const = 0;
public:
    MainTour(const std::string & flagshipEvent);
    double MinimumRankingPoints(const Tournament & tournament) const;
    
    virtual bool IsFlagShipEvent(const Tournament & tournament) const;
};

#endif /* defined(__CVATools__MainTour__) */
