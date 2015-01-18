//
//  TourAppartenance.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 14/01/15.
//
//

#include "TourAppartenance.h"
#include "PGATour.h"
#include "EuropeanTour.h"
#include "ChallengeTour.h"
#include "Exception.h"
#include "Tournament.h"
#include "WebComTour.h"
#include "AsianTour.h"
#include "JapanTour.h"
#include "SunshineTour.h"

TourAppartenance::TourAppartenance(const std::vector<TourType> & tourtypes) : m_tourTypes(tourtypes)
{
    SetTours(tourtypes);
}

void TourAppartenance::SetTours(const std::vector<TourType> &tourTypes)
{
    for (std::vector<TourType>::const_iterator it = tourTypes.begin() ; it != tourTypes.end() ; ++it)
    {
        AddTour(*it);
    }
}

void TourAppartenance::AddTour(const TourType &tourType)
{
    switch (tourType)
    {
        case PGATOUR:
            m_tours.push_back(std::tr1::shared_ptr<Tour>(new PGATour));
            break;
            
        case EUROPEANTOUR:
            m_tours.push_back(std::tr1::shared_ptr<Tour>(new EuropeanTour));
            break;
            
        case CHALLENGETOUR:
            m_tours.push_back(std::tr1::shared_ptr<Tour>(new ChallengeTour));
            break;
            
        case WEBCOMTOUR:
            m_tours.push_back(std::tr1::shared_ptr<Tour>(new WebComTour));
            break;
            
        case ASIANTOUR:
            m_tours.push_back(std::tr1::shared_ptr<Tour>(new AsianTour));
            break;
            
        case JAPANTOUR:
            m_tours.push_back(std::tr1::shared_ptr<Tour>(new JapanTour));
            break;
            
        case SUNSHINETOUR:
            m_tours.push_back(std::tr1::shared_ptr<Tour>(new SunshineTour));
            break;
            
        default:
            throw EXCEPTION("Tour Type not recognized");
    }
}

double TourAppartenance::MinimumRankingPoints(const Tournament &tournament) const
{
    double max = 0;
    for (std::vector<Tour_ptr>::const_iterator tour = m_tours.begin() ; tour != m_tours.end() ; ++tour)
    {
        max = std::max(max, (*tour)->MinimumRankingPoints(tournament));
    }
    return max;
}

bool TourAppartenance::CoSanctionedEvent() const
{
    return m_tours.size() > 1;
}