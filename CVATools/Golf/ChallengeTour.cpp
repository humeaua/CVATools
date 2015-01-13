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

ChallengeTour::ChallengeTour() : Tour("Grand Final")
{}

double ChallengeTour::MinimumNormalTournament() const
{
    return 12.0;
}

double ChallengeTour::MinimumRankingPointsFlagShipEvent() const
{
    return 17.0;
}