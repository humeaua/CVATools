//
//  RankingPointSystem.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 03/01/15.
//
//

#ifndef __CVATools__RankingPointSystem__
#define __CVATools__RankingPointSystem__

#include <iostream>
#include "PointSystem.h"
#include <tr1/memory>
#include "Rankings.h"

class RankingPointSystem : public PointSystem, protected Rankings
{
public:
    RankingPointSystem(const Rankings & ranking);
    
    // I am currently implementing those rules on the current ranking of the players
    double HomeRatingValue(const Tournament & tournament) const;
    double WorldEventRatingValue(const Tournament & tournament) const;
};

#endif /* defined(__CVATools__RankingPointSystem__) */
