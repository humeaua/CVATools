//
//  PlayerID.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 17/12/14.
//
//

#include "PlayerID.h"

PlayerID::PlayerID(const std::string & name) : m_name(name)
{}

const std::string & PlayerID::Name() const
{
    return m_name;
}

std::ostream & operator<<(std::ostream & os, const PlayerID & playerId)
{
    os << playerId.Name();
    return os;
}