//
//  WebComTour.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 15/01/15.
//
//

#include "WebComTour.h"

WebComTour::WebComTour() : MainTour("Tour Championship")
{}

double WebComTour::MinimumRankingPointsNormalTournament() const
{
    return 14.0;
}

double WebComTour::MinimumRankingPointsFlagShipEvent() const
{
    return 20.0;
}