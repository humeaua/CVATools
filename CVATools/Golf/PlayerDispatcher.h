//
//  PlayerDispatcher.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 07/03/15.
//
//

#ifndef __CVATools__PlayerDispatcher__
#define __CVATools__PlayerDispatcher__

#include <iostream>
#include "BernouilliGenerator.h"
#include <vector>

class Player;
class Tournament;

class PlayerDispatcher
{
private:
    void AddPlayerToTournament(const double randomValue, Tournament & tournament, Player & player) const;
protected:
    BernouilliGenerator m_inTour, m_outsideTour;
public:
    PlayerDispatcher(const double & proba_in, const double & proba_out, long long & seed);
    
    virtual void Dispatch(std::vector<Player> & players, std::vector<Tournament> & tournaments);
    
};

#endif /* defined(__CVATools__PlayerDispatcher__) */
