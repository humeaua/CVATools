//
//  EuropeanTour.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 07/01/15.
//
//

#include "EuropeanTour.h"
#include "StringUtilities.h"
#include "Tournament.h"

bool EuropeanTour::IsFlagShipEvent(const Tournament &tournament) const
{
    const std::string tournamentName = Utilities::ToUpperCopy(tournament.TournamentName());
    return tournamentName == "BMW PGA CHAMPIONSHIP";
}

double EuropeanTour::MinimumRankingPoints(const Tournament &tournament) const
{
    if (IsFlagShipEvent(tournament))
    {
        return 64.0;
    }
    else
    {
        return 24.0; // to be done properly need to take into account the total rating values
    }
}