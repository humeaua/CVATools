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

namespace {
    //template<class C, class D>
    //inline bool GreaterSecond(const std::pair<C, D> & lhs, const std::pair<C, D> & rhs)
    inline bool GreaterSecond(const std::pair<PlayerID, double> & lhs, const std::pair<PlayerID, double> & rhs)
    {
        return lhs.second > rhs.second;
    }
}

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
    std::sort(realRanking.begin(), realRanking.end(), GreaterSecond);
    
    return realRanking;
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
        
        const std::vector<std::pair<Utilities::Date::MyDate, double> > results = m_ranking[i].second.GetResults();
        for (size_t tournament = 0 ; tournament < results.size() ; ++tournament)
        {
            const double diffInYear = computedDate.Diff(results[tournament].first);
            mean += results[tournament].second * m_interpolator(diffInYear);
        }
        
        m_realRanking[i].second = mean;
    }
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