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
#include <tr1/memory>

//  Base class for the tours
class Tournament;

class Tour
{
protected:
    std::string m_flagshipEventName;
    
    virtual double MinimumRankingPointsFlagShipEvent() const = 0;
    virtual double MinimumNormalTournament() const = 0;
public:
    Tour(const std::string & flagshipEvent);
    virtual bool IsFlagShipEvent(const Tournament & tournament) const;
    virtual double MinimumRankingPoints(const Tournament & tournament) const;
};

typedef std::tr1::shared_ptr<Tour> Tour_ptr;

enum TourType
{
    PGATOUR,
    EUROPEANTOUR,
    CHALLENGETOUR,
    WEBCOMTOUR,
    ASIANTOUR
};

#endif /* defined(__CVATools__Tour__) */
