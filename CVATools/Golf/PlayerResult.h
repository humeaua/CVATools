//
//  PlayerResult.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 14/12/14.
//
//

#ifndef __CVATools__PlayerResult__
#define __CVATools__PlayerResult__

#include <iostream>
#include "TournamentID.h"

class PlayerResult : public TournamentID
{
protected:
    size_t m_position;
    size_t m_score;
    
    double m_rankingPoints;
    bool m_missedCut;
public:
    PlayerResult(const std::string & tournamentName, const Utilities::Date::MyDate & tournamentDate, size_t position, size_t score, double rankingPoints);
    PlayerResult(const std::string & tournamentName, const Utilities::Date::MyDate & tournamentDate);
    
    // Getters and Setter
    const size_t & Position() const;
    size_t & Position();
    
    const size_t & Score() const;
    size_t & Score();
    
    const double & RankingPoints() const;
    double & RankingPoints();

    bool MissedCut() const;
};

#endif /* defined(__CVATools__PlayerResult__) */
