//
//  AsianTour.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 16/01/15.
//
//

#include "AsianTour.h"

AsianTour::AsianTour() : MainTour("Thailand Golf Championship")
{}

double AsianTour::MinimumRankingPointsFlagShipEvent() const
{
    return 20.0;
}

double AsianTour::MinimumRankingPointsNormalTournament() const
{
    return 14.0;
}