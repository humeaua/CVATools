//
//  RattachmentTour.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 08/02/15.
//
//

#include "RattachmentTour.h"
#include "Exception.h"
#include "TourFwdDecl.h"

TourMembership::TourMembership(const TourType & tourType) : m_tourType(tourType)
{
    Check();
    Reset();
}

void TourMembership::Check() const
{
    if (m_tourType == MAJOR)
    {
        throw EXCEPTION("Rattachement Tour cannot be major");
    }
}

void TourMembership::Reset()
{
    switch (m_tourType)
    {
        case PGATOUR:
            m_tour.reset(new PGATour);
            break;
            
        case EUROPEANTOUR:
            m_tour.reset(new EuropeanTour);
            break;
            
        case CHALLENGETOUR:
            m_tour.reset(new ChallengeTour);
            break;
            
        case WEBCOMTOUR:
            m_tour.reset(new WebComTour);
            break;
            
        case ASIANTOUR:
            m_tour.reset(new AsianTour);
            break;
            
        case JAPANTOUR:
            m_tour.reset(new JapanTour);
            break;
            
        case SUNSHINETOUR:
            m_tour.reset(new SunshineTour);
            break;
            
        case PGATOURCANADA:
            m_tour.reset(new PGATourCanada);
            break;
            
        default:
            throw EXCEPTION("Tour Type not recognized");
    }

}