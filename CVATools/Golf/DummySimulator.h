//
//  DummySimulator.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 18/12/14.
//
//

#ifndef __CVATools__DummySimulator__
#define __CVATools__DummySimulator__

#include <iostream>

class Tournament;

class DummySimulator
{
public:
    void Simulate(Tournament & tournament) const;
    void Rank(Tournament & tournament) const;
};

#endif /* defined(__CVATools__DummySimulator__) */
