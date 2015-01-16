//
//  AsianTour.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 16/01/15.
//
//

#include "AsianTour.h"

AsianTour::AsianTour() : Tour("Thailand Golf Championship")
{}

double AsianTour::MinimumRankingPointsFlagShipEvent() const
{
    return 20.0;
}

double AsianTour::MinimumNormalTournament() const
{
    return 14.0;
}