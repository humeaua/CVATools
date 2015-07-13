//
//  PlayerID.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 17/12/14.
//
//

#include "PlayerID.h"

PlayerID::PlayerID(const std::string & name, const Utilities::Date::MyDate & birthDate) : m_name(name), m_birthDate(birthDate)
{}

const std::string & PlayerID::Name() const
{
    return m_name;
}

const size_t PlayerID::Age(const Utilities::Date::MyDate &today) const
{
    return static_cast<size_t>((today.GetDays1900() - m_birthDate.GetDays1900()) / 365);
}

const Utilities::Date::MyDate & PlayerID::BirthDate() const
{
    return m_birthDate;
}

std::ostream & operator<<(std::ostream & os, const PlayerID & playerId)
{
    os << playerId.Name();
    return os;
}