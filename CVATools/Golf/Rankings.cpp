//
//  Rankings.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 21/12/14.
//
//

#include "Rankings.h"
#include "Tournament.h"
#include "PairComparatorFirst.h"

const Rankings::Ranking & Rankings::GetRanking() const
{
    return m_ranking;
}

Rankings::Ranking & Rankings::GetRanking()
{
    return m_ranking;
}

void Rankings::Compute(const std::vector<Tournament> &tournamentsThisWeek)
{
    //  Simple implementation for now
    for (std::vector<Tournament>::const_iterator tournament = tournamentsThisWeek.begin() ; tournament != tournamentsThisWeek.end() ; ++tournament)
    {
        const Tournament::Players & players = tournament->GetPlayers();
        
        //  iterate along the ranking
        for (Tournament::Players::const_iterator it = players.begin() ; it != players.end() ; ++it)
        {
            Ranking::iterator iter;
            PairComparatorFirst<Player, double, PlayerID> comp(Player((it->first.Name())));
            iter = std::find_if(m_ranking.begin(), m_ranking.end(), comp);
            if (iter != m_ranking.end())
            {
                iter->first.AddResult(*tournament);
            }
            else
            {
                //  first tournament of the player : add it in the rankings
                m_ranking.push_back(std::make_pair(Player(it->first.Name()), 0.0));
            }
        }
    }
}