//
//  ChallengeTour.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 12/01/15.
//
//

#include "ChallengeTour.h"
#include "StringUtilities.h"
#include "Tournament.h"

bool ChallengeTour::IsFlagShipEvent(const Tournament &tournament) const
{
    const std::string tournamentName = Utilities::ToUpperCopy(tournament.TournamentName());
    return tournamentName == "GRAND FINAL";
}

double ChallengeTour::MinimumRankingPoints(const Tournament &tournament) const
{
    if (IsFlagShipEvent(tournament))
    {
        return 17.0;
    }
    else
    {
        return 12.0;
    }
}