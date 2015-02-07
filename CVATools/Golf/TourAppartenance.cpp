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
    m_tours.resize(tourtypes.size());
    SetTours();
}

void TourAppartenance::SetTours()
{
    for (size_t i = 0 ; i < m_tourTypes.size() ; ++i)
    {
        AddTour(i);
    }
}

void TourAppartenance::AddTour(const size_t &i)
{
    switch (m_tourTypes[i])
    {
        case PGATOUR:
            m_tours[i].reset(new PGATour);
            break;
            
        case EUROPEANTOUR:
            m_tours[i].reset(new EuropeanTour);
            break;
            
        case CHALLENGETOUR:
            m_tours[i].reset(new ChallengeTour);
            break;
            
        case WEBCOMTOUR:
            m_tours[i].reset(new WebComTour);
            break;
            
        case ASIANTOUR:
            m_tours[i].reset(new AsianTour);
            break;
            
        case JAPANTOUR:
            m_tours[i].reset(new JapanTour);
            break;
            
        case SUNSHINETOUR:
            m_tours[i].reset(new SunshineTour);
            break;
            
        case PGATOURCANADA:
            m_tours[i].reset(new PGATourCanada);
            break;
            
        case MAJOR:
            m_tours[i].reset(new Major);
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
        WorldTour * worldTour = dynamic_cast<WorldTour*>((*tour).get());
        if (worldTour != NULL && CoSanctionedEvent())
        {
            throw EXCEPTION("World Tour event cannot be co-sanctioned");
        }
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