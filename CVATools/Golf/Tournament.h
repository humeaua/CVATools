//
//  Tournament.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 17/12/14.
//
//

#ifndef __CVATools__Tournament__
#define __CVATools__Tournament__

#include <iostream>
#include "TournamentID.h"
#include "PlayerID.h"
#include "PlayerResult.h"
#include <vector>

typedef std::vector<std::pair<PlayerID, PlayerResult> > Players;

class Tournament : public TournamentID
{
protected:
    Players m_players;
public:
    Tournament(const std::string & tournamentName, const Utilities::Date::MyDate & tournamentDate);
    
    template<class Simulator>
    void Simulate(const Simulator & tournamentSimulator)
    {
        tournamentSimulator.Simulate(*this);
    }
    
    void AddPlayer(const PlayerID & player);
    
    const Players & Players() const;
};

#endif /* defined(__CVATools__Tournament__) */
