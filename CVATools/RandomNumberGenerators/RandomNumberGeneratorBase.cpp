//
//  RandomNumberGeneratorBase.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 21/02/15.
//
//

#include "RandomNumberGeneratorBase.h"
#include "MersenneTwister.h"

RandomNumberGeneratorBase::RandomNumberGeneratorBase(long long & seed) : m_engine(new MersenneTwister19937_64(seed))
{}

RandomNumberGeneratorBase::~RandomNumberGeneratorBase()
{}

double RandomNumberGeneratorBase::operator()() const
{
    return (*m_engine)();
}