//
//  MersenneTwister.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 21/02/15.
//
//

#include "MersenneTwister.h"

MersenneTwister19937_64::MersenneTwister19937_64(long long & seed) : MCEngine(seed)
{
    m_engine.seed(seed);
}

double MersenneTwister19937_64::operator()() const
{
    return m_engine();
}