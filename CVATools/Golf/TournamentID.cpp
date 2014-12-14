//
//  TournamentID.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 14/12/14.
//
//

#include "TournamentID.h"

TournamentID::TournamentID(const std::string & tournamentName, const Utilities::Date::MyDate & tournamentDate) : m_tournamentName(tournamentName), m_tournamentDate(tournamentDate)
{}

const std::string & TournamentID::TournamentName() const
{
    return m_tournamentName;
}

std::string & TournamentID::TournamentName()
{
    return m_tournamentName;
}

const Utilities::Date::MyDate & TournamentID::TournamentDate() const
{
    return m_tournamentDate;
}

Utilities::Date::MyDate & TournamentID::TournamentDate()
{
    return m_tournamentDate;
}