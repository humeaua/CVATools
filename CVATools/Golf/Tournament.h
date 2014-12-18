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

class Tournament : public TournamentID
{
public:
    typedef std::vector<std::pair<PlayerID, PlayerResult> > Players;
    
    Tournament(const std::string & tournamentName, const Utilities::Date::MyDate & tournamentDate);
    
    template<class Simulator>
    void Simulate(const Simulator & tournamentSimulator)
    {
        tournamentSimulator.Simulate(*this);
    }
    
    template<class Simulator>
    void Rank(const Simulator & tournamentSimulator)
    {
        tournamentSimulator.Rank(*this);
    }
    
    void AddPlayer(const PlayerID & player);
    
    const Players & GetPlayers() const;
    Players & GetPlayers();
    
protected:
    Players m_players;
};

#endif /* defined(__CVATools__Tournament__) */
