//
//  JapanTour.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 17/01/15.
//
//

#include "JapanTour.h"

JapanTour::JapanTour() : MainTour("Japan Open")
{}

double JapanTour::MinimumRankingPointsFlagShipEvent() const
{
    return 32.0;
}

double JapanTour::MinimumRankingPointsNormalTournament() const
{
    return 14.0;
}