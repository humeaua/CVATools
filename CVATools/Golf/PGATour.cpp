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

PGATour::PGATour() : Tour("The Players")
{}

double PGATour::MinimumNormalTournament() const
{
    return 24.0;
}

double PGATour::MinimumRankingPointsFlagShipEvent() const
{
    return 80.0;
}