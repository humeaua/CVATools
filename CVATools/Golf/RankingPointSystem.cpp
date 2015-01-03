//
//  RankingPointSystem.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 03/01/15.
//
//

#include "RankingPointSystem.h"
#include "Tournament.h"
#include "PairComparatorFirst.h"
#include "PointsSystemStaticData.h"

RankingPointSystem::RankingPointSystem(const Rankings & ranking) : Rankings(ranking)
{}

double RankingPointSystem::HomeRatingValue(const Tournament &tournament) const
{
    const Tournament::Players & players = tournament.GetPlayers();
    double homeRatingValue = 0;
    const std::vector<double> & homeRatingValues = PointsSystemStaticData::GetHomeRatingValues();
    for (Tournament::Players::const_iterator player = players.begin() ; player != players.end() ; ++player)
    {
        const PlayerID & playerId = (const PlayerID&) *player;
        PairComparatorFirst<PlayerID, PlayerRanking> comp(playerId);
        
        const Ranking::const_iterator it = std::find_if(m_ranking.begin(), m_ranking.end(), comp);
        
        if (it == m_ranking.end())
        {
            continue;
        }
        else
        {
            size_t diff = it - m_ranking.begin();
            if (diff > homeRatingValues.size())
            {
                continue;
            }
            else
            {
                homeRatingValue += homeRatingValues[diff];
            }
        }
    }
    return homeRatingValue;
}

double RankingPointSystem::WorldEventRatingValue(const Tournament &tournament) const
{
    const Tournament::Players & players = tournament.GetPlayers();
    double worldEventRatingValue = 0;
    const std::vector<double> & worldEventRatingValues = PointsSystemStaticData::GetEventRatingValues();
    for (Tournament::Players::const_iterator player = players.begin() ; player != players.end() ; ++player)
    {
        const PlayerID & playerId = (const PlayerID&) *player;
        PairComparatorFirst<PlayerID, PlayerRanking> comp(playerId);
        
        const Ranking::const_iterator it = std::find_if(m_ranking.begin(), m_ranking.end(), comp);
        
        if (it == m_ranking.end())
        {
            continue;
        }
        else
        {
            size_t diff = it - m_ranking.begin();
            if (diff > worldEventRatingValues.size())
            {
                continue;
            }
            else
            {
                worldEventRatingValue += worldEventRatingValues[diff];
            }
        }
    }
    return worldEventRatingValue;
}
