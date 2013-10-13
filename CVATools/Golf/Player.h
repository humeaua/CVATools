//
//  Player.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 10/10/13.
//
//

#ifndef __CVATools__Player__
#define __CVATools__Player__

#include <iostream>
#include "Tournament.h"

namespace Golf
{
    class Tournament;
    
    class Player
    {
    protected:
        std::string cFirstName_, cLastName_;
        
        std::size_t iRanking_;
        std::size_t iNTournamentsPlayed_;
        
        double dTotalPoints_;
    public:
        Player(const std::string & cFirstName, const std::string & cLastName);
        Player(const std::string & cCSVFile);
        
        virtual ~Player();
        
        virtual double Average() const;
        virtual void LoadFromFile(const std::string cFileName);
        
        virtual std::pair<std::string, std::string> GetName() const;
        
        virtual bool HasPlayed(const Tournament & sTournament) const;
    };
}

#endif /* defined(__CVATools__Player__) */
