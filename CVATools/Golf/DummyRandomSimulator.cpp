//
//  DummyRandomSimulator.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 19/12/14.
//
//

#include "DummyRandomSimulator.h"
#include "Tournament.h"

DummyRandomSimulator::DummyRandomSimulator(unsigned int seed)
{
    srand(seed);
}

void DummyRandomSimulator::Simulate(Tournament &tournament) const
{
    Tournament::Players & players = tournament.GetPlayers();
    for (size_t player = 0 ; player < players.size() ; ++player)
    {
        players[player].second.Score() = rand();
    }
}