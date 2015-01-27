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
    std::vector<double> m_adjustedPoints;
public:
    void Update(const Tournament::Players & players,
                const std::vector<double> & pointsComparedToFirst);
    
    const std::vector<double> & GetAdjustedPoints() const;
};

#endif /* defined(__CVATools__TieHandler__) */
