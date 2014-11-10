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
#include "PlayerResult.h"
#include <set>
#include "OfficialWorldGolfRankings.h"

namespace Golf
{
    class Tournament;

    typedef std::set<PlayerResult> PlayerResultHandler;

    class Player
    {
    protected:
        std::string cFirstName_, cLastName_;
        
        std::size_t iRanking_;
        std::size_t iNTournamentsPlayed_;
        
        double dTotalPoints_;
        
        PlayerResultHandler mResults_;
    public:
        Player();
        Player(const std::string & cFirstName, const std::string & cLastName);
        Player(const std::string & cCSVFile, const Utilities::Date::MyDate & today);
        
        virtual ~Player();
        
        virtual double Average() const;
        virtual void ComputeTotalPoints(DiscountType eDiscountType, const Utilities::Date::MyDate & sObservationDate);
        
        virtual void LoadFromFile(const std::string cFileName, DiscountType eDiscountType, const Utilities::Date::MyDate & sDate);
        
        virtual std::pair<std::string, std::string> GetName() const;
        
        virtual bool HasPlayed(const Tournament & sTournament) const;
        
        virtual void Print(std::ostream & os = std::cout) const;
        virtual void PrintName(std::ostream & os = std::cout) const;
        
        virtual bool operator<(const Player & sRight) const;
        virtual bool operator>(const Player & sRight) const;
    };
}

#endif /* defined(__CVATools__Player__) */
