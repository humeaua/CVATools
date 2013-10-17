//
//  Tournament.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 10/10/13.
//
//

#ifndef __CVATools__Tournament__
#define __CVATools__Tournament__

#include <iostream>
#include <map>
#include "Player.h"
#include "Date.h"

namespace Golf
{
    class Player;
    typedef std::map<std::pair<std::string, std::string>, double> TournamentResults;
    //  A tournamenent is represented as a result map between the name of the player and the number of points he wins
    class Tournament
    {
    protected:
        TournamentResults mResults_;
        Utilities::Date::MyDate sDate_;
    public:
        Tournament(const TournamentResults & mResults_, const Utilities::Date::MyDate & sDate);
        Tournament(const std::string & cFileName);
        virtual ~Tournament();
        
        virtual void Add(const Player & sPlayer, double dResult);
        virtual void Add(const std::pair<std::string, std::string> & cPlayerName, double dResult);
        virtual TournamentResults GetResults() const;
        
        virtual void LoadFromFile(const std::string & cFileName);
        virtual void Print(std::ostream & cout = std::cout) const;
    };
}

#endif /* defined(__CVATools__Tournament__) */
