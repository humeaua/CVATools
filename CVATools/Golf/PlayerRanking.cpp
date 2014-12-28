//
//  PlayerRanking.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 28/12/14.
//
//

#include "PlayerRanking.h"

const std::vector<std::pair<Utilities::Date::MyDate, double> > & PlayerRanking::GetResults() const
{
    return m_results;
}

std::vector<std::pair<Utilities::Date::MyDate, double> > & PlayerRanking::GetResults()
{
    return m_results;
}

void PlayerRanking::AddResult(const Utilities::Date::MyDate &tournamentDate, const double &tournamentPoints)
{
    m_results.push_back(std::make_pair(tournamentDate, tournamentPoints));
}