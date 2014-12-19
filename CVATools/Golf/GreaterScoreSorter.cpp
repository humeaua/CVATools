//
//  GreaterScoreSorter.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 18/12/14.
//
//

#include "GreaterScoreSorter.h"
#include "Tournament.h"

namespace {
    inline bool ScoreGreaterThan(const std::pair<PlayerID, PlayerResult> & lhs, const std::pair<PlayerID, PlayerResult> & rhs)
    {
        return lhs.second.Score() > rhs.second.Score();
    }
}

void GreaterScoreSorter::Rank(Tournament & tournament) const
{
    Tournament::Players & players = tournament.GetPlayers();
    std::sort(players.begin(), players.end(), ScoreGreaterThan);
}