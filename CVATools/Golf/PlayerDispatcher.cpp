//
//  PlayerDispatcher.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 07/03/15.
//
//

#include "PlayerDispatcher.h"
#include "Player.h"
#include "Tournament.h"

PlayerDispatcher::PlayerDispatcher(const double & proba_in, const double & proba_out, long long & seed) : m_inTour(seed, proba_in), m_outsideTour(seed, proba_out)
{}

void PlayerDispatcher::Dispatch(std::vector<Player> &players, std::vector<Tournament> &tournaments)
{
    for (std::vector<Player>::iterator player = players.begin() ; player != players.end() ; ++player)
    {
        const TourType & tourMemberShip = player->GetTourMembership();
        if (!player->IsPlayerPlayingThisWeek())
        {
            for (std::vector<Tournament>::iterator tournament = tournaments.begin() ; tournament != tournaments.end() ; ++tournament)
            {
                std::vector<TourType> & tours = tournament->GetTourTypes();
                
                double value;
                if (std::find(tours.begin(), tours.end(), tourMemberShip) != tours.end())
                {
                    //  The player might play in his tour
                    value = m_inTour.operator()();
                    
                }
                else
                {
                    //  The player might play in another tour
                    value = m_outsideTour.operator()();
                }
                AddPlayerToTournament(value, *tournament, *player);
                if (player->IsPlayerPlayingThisWeek())
                {
                    break;
                }
            }
        }
    }
}

void PlayerDispatcher::AddPlayerToTournament(const double randomValue, Tournament &tournament, Player &player) const
{
    if (randomValue == 1.0)
    {
        tournament.AddPlayer((PlayerID&)player);
        player.IsPlayerPlayingThisWeek() = true;
    }
}