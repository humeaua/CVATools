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

EuropeanTour::EuropeanTour() : Tour("BMW PGA CHAMPIONSHIP")
{}

double EuropeanTour::MinimumNormalTournament() const
{
    return 24.0;
}

double EuropeanTour::MinimumRankingPointsFlagShipEvent() const
{
    return 64.0;
}