//
//  Rankings.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 21/12/14.
//
//

#ifndef __CVATools__Rankings__
#define __CVATools__Rankings__

#include <iostream>
#include "Player.h"
#include <vector>

class Tournament;

class Rankings
{
public:
    typedef std::vector<std::pair<Player, double> > Ranking;
    
    const Ranking & GetRanking() const;
    Ranking & GetRanking();
    
    void Compute(const std::vector<Tournament> & tournamentsThisWeek);
    
protected:
    Ranking m_ranking;
};

#endif /* defined(__CVATools__Rankings__) */
