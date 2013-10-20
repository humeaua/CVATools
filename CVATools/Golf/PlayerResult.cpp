//
//  PlayerResult.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 20/10/13.
//
//

#include "PlayerResult.h"
#include <cmath>

namespace Golf
{
    PlayerResult::PlayerResult(const std::string & cTournamentName, const Utilities::Date::MyDate & sTournamentDate, double dPoint): sTournamentDate_(sTournamentDate), dPoint_(dPoint), cTournamentName_(cTournamentName)
    {}
    
    PlayerResult::~PlayerResult()
    {
        sTournamentDate_.~MyDate();
    }
    
    bool PlayerResult::operator==(const Golf::PlayerResult &sRight)
    {
        return fabs(sRight.dPoint_ - dPoint_) < 0.001 && sRight.sTournamentDate_ == sTournamentDate_;
    }
    
    bool PlayerResult::operator<(const Golf::PlayerResult &sRight) const
    {
        return sTournamentDate_ < sRight.sTournamentDate_;
    }
    
    Utilities::Date::MyDate PlayerResult::GetDate() const
    {
        return sTournamentDate_;
    }
    
    double PlayerResult::GetPoint() const
    {
        return dPoint_;
    }
    
    std::string PlayerResult::GetTournamentName() const
    {
        return cTournamentName_;
    }
}