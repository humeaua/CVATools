//
//  Major.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 04/02/15.
//
//

#include "Major.h"
#include "StringUtilities.h"
#include "Tournament.h"
#include "SingleComparator.h"
#include "Exception.h"
#include <sstream>

Major::Major() : m_majorNames(4)
{
    m_majorNames[0] = "MASTERS";
    m_majorNames[1] = "US OPEN";
    m_majorNames[2] = "THE OPEN";
    m_majorNames[3] = "PGA CHAMPIONSHIP";
}

double Major::MinimumRankingPointsNormalTournament(const Tournament &tournament) const
{
    const std::string tournamentName = Utilities::ToUpperCopy(tournament.TournamentName());
    SimpleComparator<std::string> comp(tournamentName);
    std::vector<std::string>::const_iterator it = std::find_if(m_majorNames.begin(), m_majorNames.end(), comp);
    if (it != m_majorNames.end())
    {
        return 100.0;
    }
    else
    {
        std::stringstream ss;
        ss << "Name of major tournament : " << tournamentName << " not recognized";
        throw EXCEPTION(ss.str());
    }
}