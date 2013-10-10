//
//  Player.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 10/10/13.
//
//

#include "Player.h"

namespace Golf
{
    Player::Player(const std::string & cFirstName, const std::string & cLastName) : cFirstName_(cFirstName), cLastName_(cLastName)
    {}
    
    Player::Player(const std::string & cCSVFile)
    {
        LoadFromFile(cCSVFile);
    }
    
    void Player::LoadFromFile(const std::string cFileName)
    {
        //  implementation to come because the file format is not decided yet
    }
    
    double Player::Average() const
    {
        return iNTournamentsPlayed_ < 40 ? dTotalPoints_ / 40.0 : iNTournamentsPlayed_ > 52 ? dTotalPoints_ / 52 : dTotalPoints_ / iNTournamentsPlayed_;
    }
}