//
//  Tournament.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 17/12/14.
//
//

#include "Tournament.h"

Tournament::Tournament(const std::string & tournamentName, const Utilities::Date::MyDate & tournamentDate) : TournamentID(tournamentName, tournamentDate), m_PointsTo1st(0.0)
{}

void Tournament::AddPlayer(const PlayerID &player)
{
    m_players.push_back(std::pair<PlayerID, PlayerResult>(player,PlayerResult(m_tournamentName, m_tournamentDate)));
}

const Tournament::Players & Tournament::GetPlayers() const
{
    return m_players;
}

Tournament::Players & Tournament::GetPlayers()
{
    return m_players;
}

const double & Tournament::PointsTo1st() const
{
    return m_PointsTo1st;
}

double & Tournament::PointsTo1st()
{
    return m_PointsTo1st;
}