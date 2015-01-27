//
//  ValueSimulator.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 27/01/15.
//
//

#ifndef __CVATools__ValueSimulator__
#define __CVATools__ValueSimulator__

#include <iostream>

class Tournament;

class ValueSimulator
{
    size_t m_value;
public:
    ValueSimulator(size_t value);
    void Simulate(Tournament & tournament) const;
};

#endif /* defined(__CVATools__ValueSimulator__) */
