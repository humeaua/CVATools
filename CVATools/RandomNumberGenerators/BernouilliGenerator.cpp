//
//  BernouilliGenerator.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 21/02/15.
//
//

#include "BernouilliGenerator.h"

BernouilliGenerator::BernouilliGenerator(long long & seed, const double & p) : m_dist(p), RandomNumberGeneratorBase(seed)
{}

double BernouilliGenerator::operator()()
{
    return m_dist(m_engine);
}