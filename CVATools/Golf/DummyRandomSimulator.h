//
//  DummyRandomSimulator.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 19/12/14.
//
//

#ifndef __CVATools__DummyRandomSimulator__
#define __CVATools__DummyRandomSimulator__

#include <iostream>

class Tournament;

class DummyRandomSimulator
{
public:
    DummyRandomSimulator(unsigned int seed);
    void Simulate(Tournament & tournament) const;
};

#endif /* defined(__CVATools__DummyRandomSimulator__) */
