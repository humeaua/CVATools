//
//  MainTour.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 25/01/15.
//
//

#include "MainTour.h"
#include "Tournament.h"
#include "StringUtilities.h"

MainTour::MainTour(const std::string & flagshipEvent) : m_flagshipEventName(Utilities::ToUpperCopy(flagshipEvent))
{}

bool MainTour::IsFlagShipEvent(const Tournament &tournament) const
{
    return tournament.TournamentName() == m_flagshipEventName;
}

double MainTour::MinimumRankingPoints(const Tournament & tournament) const
{
    if (IsFlagShipEvent(tournament))
    {
        return MinimumRankingPointsFlagShipEvent();
    }
    else
    {
        return MinimumRankingPointsNormalTournament();
    }
}