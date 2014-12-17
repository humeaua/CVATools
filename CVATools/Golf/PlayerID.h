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

class PlayerID
{
protected:
    std::string m_name;
public:
    PlayerID(const std::string & name);
    
    const std::string & Name() const;
};

inline bool operator==(const PlayerID& lhs, const PlayerID& rhs)
{
    return lhs.Name() == rhs.Name();
}

#endif /* defined(__CVATools__PlayerID__) */
