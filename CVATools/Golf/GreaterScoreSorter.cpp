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

void GreaterScoreSorter::Rank(Tournament & tournament) const
{
    Tournament::Players & players = tournament.GetPlayers();
    std::sort(players.begin(), players.end(), ScoreGreaterThan);
    
    const OWGRVectorWrapper<double> & pointsComparedTo1st = PointsSystemStaticData::PointsComparedTo1st();
    
    // Call Tie Handler
    m_tieHandler.Update(players, pointsComparedTo1st);
    OWGRVectorWrapper<double> adjustedPoints = m_tieHandler.GetAdjustedPoints();
    
    for (size_t i = 0 ; i < players.size() ; ++i)
    {
        players[i].second.Position() = i;
        //   Adapt the ranking point system
        const double points = tournament.GetPointsTo1st() * adjustedPoints[i] * 0.01;
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