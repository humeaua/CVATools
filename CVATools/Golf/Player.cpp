//
//  Player.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 14/12/14.
//
//

#include "Player.h"
#include "Tournament.h"
#include "PairComparatorFirst.h"

Player::Player(const std::string & name) : PlayerID(name)
{}

void Player::AddResult(const PlayerResult &result)
{
    m_results.push_back(result);
}

void Player::AddResult(const Tournament &tournament)
{
    const Players & playersInTournament = tournament.Players();
    
    Players::const_iterator iter;
    PairComparatorFirst<PlayerID, PlayerResult> comp(m_name);
    iter = std::find_if(playersInTournament.begin(), playersInTournament.end(), comp);
    if (iter != playersInTournament.end())
    {
        AddResult(iter->second);
    }
}

bool Player::IsCorrectPlayer(const std::pair<PlayerID, PlayerResult> &player) const
{
    // Assume that the name is unique
    return player.first.Name() == m_name;
}