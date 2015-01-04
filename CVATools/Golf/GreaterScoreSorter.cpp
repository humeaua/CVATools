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
    
    const std::vector<double> & pointsComparedTo1st = PointsSystemStaticData::PointsComparedTo1st();
    
    for (size_t i = 0 ; i < players.size() ; ++i)
    {
        players[i].second.Position() = i;
        //   Adapt the ranking point system
        if (i < pointsComparedTo1st.size())
        {
            players[i].second.RankingPoints() = tournament.GetPointsTo1st() * pointsComparedTo1st[i] * 0.01;
        }
        else
        {
            players[i].second.RankingPoints() = tournament.GetPointsTo1st() * pointsComparedTo1st.back() * 0.01;
        }
    }
    
    
}