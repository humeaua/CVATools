//
//  Major.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 04/02/15.
//
//

#ifndef __CVATools__Major__
#define __CVATools__Major__

#include <iostream>
#include "WorldTour.h"
#include <vector>

class Major : public WorldTour
{
protected:
    std::vector<std::string> m_majorNames;
    
    double MinimumRankingPointsNormalTournament(const Tournament & tournament) const;
public:
    Major();
};

#endif /* defined(__CVATools__Major__) */
