//
//  TourAppartenance.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 14/01/15.
//
//

#ifndef __CVATools__TourAppartenance__
#define __CVATools__TourAppartenance__

#include <iostream>
#include "Tour.h"
#include <vector>

class Tournament;

class TourAppartenance
{
protected:
    std::vector<Tour_ptr> m_tours;
    std::vector<TourType> m_tourTypes;
    
public:
    TourAppartenance(const std::vector<TourType> & tourtypes);
    virtual bool CoSanctionedEvent() const;
    virtual double MinimumRankingPoints(const Tournament & tournament) const;
    
private:
    void SetTours();
    void AddTour(const size_t & i);
};

#endif /* defined(__CVATools__TourAppartenance__) */
