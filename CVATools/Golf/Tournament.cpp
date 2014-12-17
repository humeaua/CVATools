//
//  Tournament.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 17/12/14.
//
//

#include "Tournament.h"

Tournament::Tournament(const std::string & tournamentName, const Utilities::Date::MyDate & tournamentDate) : TournamentID(tournamentName, tournamentDate)
{}

void Tournament::AddPlayer(const PlayerID &player)
{
    m_players.push_back(std::pair<PlayerID, PlayerResult>(player,PlayerResult(m_tournamentName, m_tournamentDate)));
}

const Players & Tournament::Players() const
{
    return m_players;
}