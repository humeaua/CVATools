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

Player::Player(const std::string & name, const TourType & tourType, const Utilities::Date::MyDate & birthDate) : PlayerID(name, birthDate), m_tourMembership(tourType), m_isPlayingThisWeek(false)
{}

void Player::AddResult(const PlayerResult &result)
{
    m_results.push_back(result);
}

void Player::AddResult(const Tournament &tournament)
{
    const Tournament::Players & playersInTournament = tournament.GetPlayers();
    
    Tournament::Players::const_iterator iter;
    PairComparatorFirst<PlayerID, PlayerResult> comp(PlayerID(m_name, m_birthDate));
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

bool & Player::IsPlayerPlayingThisWeek()
{
    return m_isPlayingThisWeek;
}

const bool & Player::IsPlayerPlayingThisWeek() const
{
    return m_isPlayingThisWeek;
}

const TourType & Player::GetTourMembership() const
{
    return m_tourMembership.GetTourType();
}

void Player::SetTourMembership(const TourType &eType)
{
    m_tourMembership = TourMembership(eType);
}