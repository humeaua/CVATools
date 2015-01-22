//
//  GreaterScoreSorter.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 18/12/14.
//
//

#ifndef __CVATools__GreaterScoreSorter__
#define __CVATools__GreaterScoreSorter__

#include <iostream>
#include "TieHandler.h"

class Tournament;

class GreaterScoreSorter
{
protected:
    //  the following variable is mutable since I cannot change the template method in Tournament
    mutable TieHandler m_tieHandler;
    bool m_useTieHandler;
public:
    GreaterScoreSorter(bool useTieHandler);
    void Rank(Tournament & tournament) const;
};

#endif /* defined(__CVATools__DummySimulator__) */
