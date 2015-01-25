//
//  TourAppartenance.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 14/01/15.
//
//

#include "TourAppartenance.h"
#include "Exception.h"
#include "Tournament.h"
#include "TourFwdDecl.h"

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
            
        case PGATOURCANADA:
            m_tours.push_back(std::tr1::shared_ptr<Tour>(new PGATourCanada));
            break;
            
        default:
            throw EXCEPTION("Tour Type not recognized");
    }
}

double TourAppartenance::MinimumRankingPoints(const Tournament &tournament) const
{
    double avg = 0;
    for (std::vector<Tour_ptr>::const_iterator tour = m_tours.begin() ; tour != m_tours.end() ; ++tour)
    {
        avg += (*tour)->MinimumRankingPoints(tournament);
    }
    if (m_tours.empty())
    {
        throw EXCEPTION("Number of tours is zero");
    }
    return avg / m_tours.size();
}

bool TourAppartenance::CoSanctionedEvent() const
{
    return m_tours.size() > 1;
}