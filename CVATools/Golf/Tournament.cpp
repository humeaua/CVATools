//
//  Tournament.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 10/10/13.
//
//

#include "Tournament.h"

namespace Golf {
    
    Tournament::Tournament(const TournamentResults & mResults, const Utilities::Date::MyDate & sDate) : mResults_(mResults), sDate_(sDate)
    {}
    
    Tournament::~Tournament()
    {
        mResults_.clear();
        sDate_.~MyDate();
    }
    
    void Tournament::Add(const Player & sPlayer, double dResult)
    {
        if (mResults_.count(sPlayer.GetName()))
        {
            mResults_[sPlayer.GetName()] = dResult;
        }
        else
        {
            mResults_.find(sPlayer.GetName())->second = dResult;
        }
    }
    
    void Tournament::Add(const std::pair<std::string, std::string> & cPlayerName, double dResult)
    {
        if (mResults_.count(cPlayerName) != 0)
        {
            mResults_[cPlayerName] = dResult;
        }
        else
        {
            mResults_.find(cPlayerName)->second = dResult;
        }
    }
    
    TournamentResults Tournament::GetResults() const
    {
        return mResults_;
    }
}