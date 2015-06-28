//
//  Rankings.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 21/12/14.
//
//

#include "Rankings.h"
#include "Tournament.h"
#include "PairComparatorFirst.h"

Rankings::Rankings(Utilities::Interp::Interpolator & interpolator) : m_interpolator(interpolator)
{}

const Rankings::Ranking & Rankings::GetRanking() const
{
    return m_ranking;
}

Rankings::Ranking & Rankings::GetRanking()
{
    return m_ranking;
}

Rankings::RealRanking Rankings::GetSortedRanking() const
{
    RealRanking realRanking = m_realRanking;
    std::sort(realRanking.begin(), realRanking.end(),
              [](const std::pair<PlayerID, double> &left, const std::pair<PlayerID, double> &right)
    {
        return left.second > right.second;
    }
              );
    
    return realRanking;
}

void Rankings::SortRanking()
{
    std::sort(m_realRanking.begin(), m_realRanking.end(),
              [](const std::pair<PlayerID, double> &left, const std::pair<PlayerID, double> &right)
              {
                  return left.second > right.second;
              }
              );
}

void Rankings::ComputeRealRanking(const Utilities::Date::MyDate &computedDate)
{
    if (m_realRanking.size() != m_ranking.size())
    {
        for (size_t i = m_realRanking.size() ; i < m_ranking.size() ; ++i)
        {
            m_realRanking.push_back(std::make_pair(m_ranking[i].first, 0.0));
        }
    }
    
    for (size_t i = 0 ; i < m_realRanking.size() ; ++i)
    {
        double mean = 0;
        
        const std::vector<std::pair<Utilities::Date::MyDate, double> > & results = m_ranking[i].second.GetResults();
        for (size_t tournament = 0 ; tournament < results.size() ; ++tournament)
        {
            const double diffInYear = computedDate.Diff(results[tournament].first);
            mean += results[tournament].second * m_interpolator(diffInYear);
        }
        const size_t nbTournamentPlayed = AdaptNumberTournamentPlayed(m_ranking[i].second, computedDate);
        m_realRanking[i].second = mean / nbTournamentPlayed;
    }
}

size_t Rankings::AdaptNumberTournamentPlayed(const PlayerRanking &playerRanking, const Utilities::Date::MyDate &computedDate) const
{
    size_t nbTournamentPlayed = 0;
    const std::vector<std::pair<Utilities::Date::MyDate, double> > & results = playerRanking.GetResults();
    for (size_t tournament = 0 ; tournament < results.size() ; ++tournament)
    {
        const double diffInYear = computedDate.Diff(results[tournament].first);
        if (m_interpolator(diffInYear))
        {
            nbTournamentPlayed++;
        }
    }
    return std::max(static_cast<unsigned long>(40), std::min(nbTournamentPlayed,static_cast<unsigned long>(52)));
}

void Rankings::Compute(const std::vector<Tournament> &tournamentsThisWeek, const Utilities::Date::MyDate & computedDate)
{
    //  Simple implementation for now
    for (std::vector<Tournament>::const_iterator tournament = tournamentsThisWeek.begin() ; tournament != tournamentsThisWeek.end() ; ++tournament)
    {
        const Tournament::Players & players = tournament->GetPlayers();
        
        //  iterate along the ranking
        for (Tournament::Players::const_iterator it = players.begin() ; it != players.end() ; ++it)
        {
            Ranking::iterator iter;
            PairComparatorFirst<PlayerID, PlayerRanking> comp(PlayerID((it->first.Name())));
            iter = std::find_if(m_ranking.begin(), m_ranking.end(), comp);
            if (iter != m_ranking.end())
            {
                iter->second.AddResult(tournament->TournamentDate(), it->second.RankingPoints());
            }
            else
            {
                //  first tournament of the player : add it in the rankings
                PlayerRanking playerRanking;
                playerRanking.AddResult(tournament->TournamentDate(), it->second.RankingPoints());
                m_ranking.push_back(std::make_pair(PlayerID(it->first.Name()), playerRanking));
            }
        }
    }
    
    //  At the end compute the ranking of the players
    ComputeRealRanking(computedDate);
}

Rankings * Rankings::clone() const
{
    return new Rankings(*this);
}

std::string Rankings::ToString() const
{
    const Rankings::RealRanking & realRanking = GetSortedRanking();
    std::stringstream os;
    for (size_t i = 0 ; i < realRanking.size() ; ++i)
    {
        os << realRanking[i].first << " : " << realRanking[i].second << std::endl;
    }
    return os.str();
}