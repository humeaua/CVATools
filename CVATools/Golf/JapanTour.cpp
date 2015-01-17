//
//  JapanTour.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 17/01/15.
//
//

#include "JapanTour.h"

JapanTour::JapanTour() : Tour("Japan Open")
{}

double JapanTour::MinimumRankingPointsFlagShipEvent() const
{
    return 20.0;
}

double JapanTour::MinimumNormalTournament() const
{
    return 14.0;
}