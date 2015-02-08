//
//  Player.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 14/12/14.
//
//

#ifndef __CVATools__Player__
#define __CVATools__Player__

#include <iostream>
#include <vector>
#include "PlayerResult.h"
#include "PlayerID.h"
#include "Tour.h"
#include "RattachmentTour.h"

class Tournament;

class Player : public PlayerID
{
protected:
    std::vector<PlayerResult> m_results;
    RattachementTour m_rattachementTour;
    
    virtual void AddResult(const PlayerResult & result);
public:
    Player(const std::string & name, const TourType & tourType);
    
    void AddResult(const Tournament & tournament);
    
    const std::vector<PlayerResult> & Results() const;
};

#endif /* defined(__CVATools__Player__) */
