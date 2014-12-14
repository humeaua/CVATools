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

class PlayerResult
{
protected:
    std::string m_tournamentName;
    size_t m_position;
    size_t m_score;
    
    double m_rankingPoints;
    bool m_missedCut;
public:
    PlayerResult(const std::string & tournamentName, size_t position, size_t score, double rankingPoints);
    
    // Getters and Setters
    const std::string & TournamentName() const;
    std::string & TournamentName();
    
    const size_t & Position() const;
    size_t & Position();
    
    const size_t & Score() const;
    size_t & Score();
    
    const double & RankingPoints() const;
    double & RankingPoints();

    const bool & MissedCut() const;
    bool& MissedCut();
};

#endif /* defined(__CVATools__PlayerResult__) */
