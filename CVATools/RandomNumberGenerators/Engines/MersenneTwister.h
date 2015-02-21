//
//  MersenneTwister.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 21/02/15.
//
//

#ifndef __CVATools__MersenneTwister__
#define __CVATools__MersenneTwister__

#include <iostream>
#include "MCEngine.h"
#include <tr1/random>

class MersenneTwister19937_64 : public MCEngine
{
protected:
    mutable std::tr1::mt19937 m_engine;
public:
    MersenneTwister19937_64(long long & seed);
    
    double operator()() const;
};

#endif /* defined(__CVATools__MersenneTwister__) */
