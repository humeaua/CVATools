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

EuropeanTour::EuropeanTour() : MainTour("BMW PGA CHAMPIONSHIP")
{}

double EuropeanTour::MinimumRankingPointsNormalTournament() const
{
    return 24.0;
}

double EuropeanTour::MinimumRankingPointsFlagShipEvent() const
{
    return 64.0;
}