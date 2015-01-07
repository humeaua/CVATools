//
//  Tournament.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 17/12/14.
//
//

#include "Tournament.h"
#include "PointsSystemStaticData.h"
#include "PointSystem.h"
#include "Exception.h"
#include "PGATour.h"
#include "EuropeanTour.h"

Tournament::Tournament(const std::string & tournamentName, const Utilities::Date::MyDate & tournamentDate, const TourType& tourType) : TournamentID(tournamentName, tournamentDate), m_PointsTo1st(0.0)
{
    SetTour(tourType);
}

void Tournament::AddPlayer(const PlayerID &player)
{
    m_players.push_back(std::pair<PlayerID, PlayerResult>(player,PlayerResult(m_tournamentName, m_tournamentDate)));
}

const Tournament::Players & Tournament::GetPlayers() const
{
    return m_players;
}

Tournament::Players & Tournament::GetPlayers()
{
    return m_players;
}

const double & Tournament::GetPointsTo1st() const
{
    return m_PointsTo1st;
}

void Tournament::PostProcessTourPoints()
{
    m_PointsTo1st = m_tour->MinimumRankingPoints(*this);
}

void Tournament::SetPointsTo1st(const PointSystem &pointSystem)
{
    const Utilities::Interp::Interpolator & interpolator = PointsSystemStaticData::GetTotalRatingToFirstPointInterpolator();
    m_PointsTo1st = interpolator(pointSystem.TotalRatingValue(*this));
    PostProcessTourPoints();
}

void Tournament::SetTour(const TourType &tourType)
{
    switch (tourType)
    {
        case PGATOUR:
            m_tour.reset(new PGATour);
            break;
            
        case EUROPEANTOUR:
            m_tour.reset(new EuropeanTour);
            break;
            
        default:
            throw EXCEPTION("Tour Type not recognized");
            break;
    }
}