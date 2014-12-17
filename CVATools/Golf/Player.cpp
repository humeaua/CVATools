//
//  Player.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 14/12/14.
//
//

#include "Player.h"

Player::Player(const std::string & name) : PlayerID(name)
{}

void Player::AddResult(const PlayerResult &result)
{
    m_results.push_back(result);
}