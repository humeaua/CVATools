//
//  PlayerResult.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 14/12/14.
//
//

#include "PlayerResult.h"
#include <iostream>

PlayerResult::PlayerResult(const std::string & tournamentName, size_t position, size_t score, double rankingPoints) : m_tournamentName(tournamentName), m_position(position), m_score(score), m_rankingPoints(rankingPoints), m_missedCut(m_rankingPoints == 0.0)
{}

const std::string & PlayerResult::TournamentName() const
{
    return m_tournamentName;
}

std::string & PlayerResult::TournamentName()
{
    return m_tournamentName;
}

const size_t & PlayerResult::Position() const
{
    return m_position;
}

size_t & PlayerResult::Position()
{
    return m_position;
}

const size_t & PlayerResult::Score() const
{
    return m_score;
}

size_t & PlayerResult::Score()
{
    return m_score;
}

const double & PlayerResult::RankingPoints() const
{
    return m_rankingPoints;
}

double & PlayerResult::RankingPoints()
{
    return m_rankingPoints;
}

const bool & PlayerResult::MissedCut() const
{
    return m_missedCut;
}

bool & PlayerResult::MissedCut()
{
    return m_missedCut;
}