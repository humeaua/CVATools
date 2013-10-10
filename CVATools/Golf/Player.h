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

namespace Golf
{
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
        
        virtual double Average() const;
        virtual void LoadFromFile(const std::string cFileName);
    };
}

#endif /* defined(__CVATools__Player__) */
