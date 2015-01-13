//
//  Tour.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 13/01/15.
//
//

#include "Tour.h"
#include "StringUtilities.h"
#include "Tournament.h"

Tour::Tour(const std::string & flagshipEvent) : m_flagshipEventName(Utilities::ToUpperCopy(flagshipEvent))
{}

bool Tour::IsFlagShipEvent(const Tournament &tournament) const
{
    return tournament.TournamentName() == m_flagshipEventName;
}

double Tour::MinimumRankingPoints(const Tournament &tournament) const
{
    if (IsFlagShipEvent(tournament))
    {
        return MinimumRankingPointsFlagShipEvent();
    }
    else
    {
        return MinimumNormalTournament();
    }
}