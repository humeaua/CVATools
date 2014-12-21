//
//  PGATour.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 21/12/14.
//
//

#include "PGATour.h"
#include "Tournament.h"
#include "StringUtilities.h"

bool PGATour::IsFlagShipEvent(const Tournament &tournament) const
{
    const std::string tournamentName = Utilities::ToUpperCopy(tournament.TournamentName());
    return tournamentName == "Players";
}

double PGATour::MinimumRankingPoints(const Tournament &tournament) const
{
    if (IsFlagShipEvent(tournament))
    {
        return 80.0;
    }
    else
    {
        return 24.0; // to be done properly need to take into account the total rating values
    }
}