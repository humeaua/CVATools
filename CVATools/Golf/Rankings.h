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
#include "PlayerID.h"
#include <vector>
#include "PlayerRanking.h"
#include "InterExtrapolation.h"

class Tournament;

class Rankings
{
    void ComputeRealRanking(const Utilities::Date::MyDate & computedDate);
public:
    Rankings(Utilities::Interp::Interpolator & interpolator);
    typedef std::vector<std::pair<PlayerID, PlayerRanking> > Ranking;
    typedef std::vector<std::pair<PlayerID, double>> RealRanking;
    
    const Ranking & GetRanking() const;
    Ranking & GetRanking();
    
    // The following method sorts the players according to their OWGR rankings
    RealRanking GetSortedRanking() const;
    
    void Compute(const std::vector<Tournament> & tournamentsThisWeek,
                 const Utilities::Date::MyDate & computedDate);
    
    Rankings * clone() const;
    
protected:
    Utilities::Interp::Interpolator & m_interpolator;
    Ranking m_ranking;
    
    RealRanking m_realRanking; // real ranking published on OWGR
};

#endif /* defined(__CVATools__Rankings__) */
