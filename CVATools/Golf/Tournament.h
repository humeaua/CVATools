//
//  Tournament.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 17/12/14.
//
//

#ifndef __CVATools__Tournament__
#define __CVATools__Tournament__

#include <iostream>
#include "TournamentID.h"
#include "PlayerID.h"
#include "PlayerResult.h"
#include <vector>
#include "TourAppartenance.h"

class PointSystem;

class Tournament : public TournamentID, public TourAppartenance
{
public:
    typedef std::vector<std::pair<PlayerID, PlayerResult> > Players;
    
    Tournament(const std::string & tournamentName, const Utilities::Date::MyDate & tournamentDate, const std::vector<TourType> & tourType);
    
    template<class Simulator>
    void Simulate(const Simulator & tournamentSimulator)
    {
        tournamentSimulator.Simulate(*this);
    }
    
    template<class Simulator>
    void Rank(const Simulator & tournamentSimulator)
    {
        tournamentSimulator.Rank(*this);
    }
    
    void AddPlayer(const PlayerID & player);
    
    const Players & GetPlayers() const;
    Players & GetPlayers();
    
    const double & GetPointsTo1st() const;
    void SetPointsTo1st(const PointSystem & pointSystem);
    
    std::vector<TourType> & GetTourTypes();
    
protected:
    double m_PointsTo1st;
    Players m_players;
    std::vector<Tour_ptr> m_tours;
    std::vector<TourType> m_tourType;
private:
    void PostProcessTourPoints();
};

#endif /* defined(__CVATools__Tournament__) */
