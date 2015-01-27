//
//  GreaterScoreSorter.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 18/12/14.
//
//

#include "GreaterScoreSorter.h"
#include "Tournament.h"
#include "PointsSystemStaticData.h"

namespace {
    inline bool ScoreGreaterThan(const std::pair<PlayerID, PlayerResult> & lhs, const std::pair<PlayerID, PlayerResult> & rhs)
    {
        return lhs.second.Score() > rhs.second.Score();
    }
}

GreaterScoreSorter::GreaterScoreSorter(bool useTieHandler) : m_useTieHandler(useTieHandler)
{}

void GreaterScoreSorter::Rank(Tournament & tournament) const
{
    Tournament::Players & players = tournament.GetPlayers();
    std::sort(players.begin(), players.end(), ScoreGreaterThan);
    
    //  Enable Tie handler when the class is fully working
    std::vector<double> & pointsComparedTo1st = PointsSystemStaticData::PointsComparedTo1st();
    if (m_useTieHandler)
    {
        m_tieHandler.Update(players, pointsComparedTo1st);
        pointsComparedTo1st = m_tieHandler.GetAdjustedPoints();
    }
    
    for (size_t i = 0 ; i < players.size() ; ++i)
    {
        players[i].second.Position() = i;
        //   Adapt the ranking point system
        if (i < pointsComparedTo1st.size())
        {
            const double points = tournament.GetPointsTo1st() * pointsComparedTo1st[i] * 0.01;
            if (points >= 1.0)
            {
                players[i].second.RankingPoints() = points;
            }
            else
            {
                // If the number of points is below 1, then it is 0
                players[i].second.RankingPoints() = 0.0;
            }
        }
        else
        {
            const double points = tournament.GetPointsTo1st() * pointsComparedTo1st.back() * 0.01;
            if (points >= 1.0)
            {
                players[i].second.RankingPoints() = points;
            }
            else
            {
                // If the number of points is below 1, then it is 0
                players[i].second.RankingPoints() = 0.0;
            }
        }
    }
}