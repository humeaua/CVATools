//
//  WorldTour.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 04/02/15.
//
//

#include "WorldTour.h"
#include "Exception.h"

double WorldTour::MinimumRankingPointsNormalTournament() const
{
    throw EXCEPTION("MinimumRankingPointsNormalTournament not implemented for World Tour");
}

double WorldTour::MinimumRankingPoints(const Tournament &tournament) const
{
    return MinimumRankingPointsNormalTournament(tournament);
}