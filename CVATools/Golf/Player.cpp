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

Player::Player(const std::string & name, const TourType & tourType) : PlayerID(name), m_rattachementTour(tourType)
{}

void Player::AddResult(const PlayerResult &result)
{
    m_results.push_back(result);
}

void Player::AddResult(const Tournament &tournament)
{
    const Tournament::Players & playersInTournament = tournament.GetPlayers();
    
    Tournament::Players::const_iterator iter;
    PairComparatorFirst<PlayerID, PlayerResult> comp(m_name);
    iter = std::find_if(playersInTournament.begin(), playersInTournament.end(), comp);
    if (iter != playersInTournament.end())
    {
        AddResult(iter->second);
    }
}

const std::vector<PlayerResult> & Player::Results() const
{
    return m_results;
}