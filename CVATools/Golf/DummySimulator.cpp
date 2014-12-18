//
//  DummySimulator.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 18/12/14.
//
//

#include "DummySimulator.h"
#include "Tournament.h"

namespace {
    inline bool ScoreGreaterThan(const std::pair<PlayerID, PlayerResult> & lhs, const std::pair<PlayerID, PlayerResult> & rhs)
    {
        return lhs.second.Score() > rhs.second.Score();
    }
}

void DummySimulator::Simulate(Tournament & tournament) const
{}

void DummySimulator::Rank(Tournament & tournament) const
{
    Tournament::Players & players = tournament.GetPlayers();
    std::sort(players.begin(), players.end(), ScoreGreaterThan);
}