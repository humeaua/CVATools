//
//  TieHandler.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 22/01/15.
//
//

#include "TieHandler.h"
#include <numeric>

void TieHandler::Update(const Tournament::Players & players,
                        const OWGRVectorWrapper<double> & pointsComparedToFirst)
{
    m_adjustedPoints.resize(players.size());
    
    for (size_t player = 0 ; player < players.size() ; ++player)
    {
        size_t endPoint = player;
        for ( ; endPoint < players.size() ; ++endPoint)
        {
            if (players[player].second.Score() != players[endPoint].second.Score())
            {
                break;
            }
        }
        ///////////////////////////////////////////////////////////////
        // Need to be careful here -- THIS IS NOT CORRECT YET !!!!!! //
        ///////////////////////////////////////////////////////////////
        // The size of PointsComparedToFirst may be not equal to Player (smaller) and it might create random access violation
        double totalPoints = 0.0;
        for (size_t i = player ; i < endPoint ; ++i)
        {
            totalPoints += pointsComparedToFirst[i];
        }
        for (size_t i = player ; i < endPoint ; ++i)
        {
            m_adjustedPoints.vector()[i] = totalPoints / (endPoint - player);
        }
        
        player += endPoint;
    }
}

const OWGRVectorWrapper<double> & TieHandler::GetAdjustedPoints() const
{
    return m_adjustedPoints;
}