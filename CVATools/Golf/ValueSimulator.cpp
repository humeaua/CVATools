//
//  ValueSimulator.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 27/01/15.
//
//

#include "ValueSimulator.h"
#include "Tournament.h"

ValueSimulator::ValueSimulator(size_t value) : m_value(value)
{}

void ValueSimulator::Simulate(Tournament &tournament) const
{
    Tournament::Players & players = tournament.GetPlayers();
    for (size_t player = 0 ; player < players.size() ; ++player)
    {
        players[player].second.Score() = m_value;
    }
}