//
//  TieHandler.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 22/01/15.
//
//

#ifndef __CVATools__TieHandler__
#define __CVATools__TieHandler__

#include <iostream>
#include <map>
#include "Tournament.h"

//  The goal of this class is to handle tie in a tournament and hence have the possibility to share the ranking points amongst several players

class TieHandler
{
protected:
    std::map<size_t, size_t> m_positionsToNumber;
public:
    void Update(const Tournament::Players & players);
};

#endif /* defined(__CVATools__TieHandler__) */