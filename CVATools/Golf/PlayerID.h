//
//  PlayerID.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 17/12/14.
//
//

#ifndef __CVATools__PlayerID__
#define __CVATools__PlayerID__

#include <iostream>
#include "Date.h"

class PlayerID
{
protected:
    std::string m_name;
    Utilities::Date::MyDate m_birthDate;
public:
    PlayerID(const std::string & name, const Utilities::Date::MyDate & birthdate);
    
    const std::string & Name() const;
    const size_t Age(const Utilities::Date::MyDate & today) const;
    const Utilities::Date::MyDate & BirthDate() const;
};

inline bool operator==(const PlayerID& lhs, const PlayerID& rhs)
{
    return lhs.Name() == rhs.Name();
}

std::ostream & operator <<(std::ostream & os, const PlayerID & playerId);

#endif /* defined(__CVATools__PlayerID__) */
