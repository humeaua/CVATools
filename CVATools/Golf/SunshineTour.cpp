//
//  SunshineTour.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 18/01/15.
//
//

#include "SunshineTour.h"

SunshineTour::SunshineTour() : MainTour("South African Open")
{}

double SunshineTour::MinimumRankingPointsFlagShipEvent() const
{
    return 32.0;
}

double SunshineTour::MinimumRankingPointsNormalTournament() const
{
    return 14.0;
}