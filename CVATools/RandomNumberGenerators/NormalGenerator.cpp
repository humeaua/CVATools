//
//  NormalGenerator.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 28/02/15.
//
//

#include "NormalGenerator.h"

NormalGenerator::NormalGenerator(long long & seed, const double & mean, const double & stdev) : m_engine(seed), m_dist(mean, stdev)
{}

double NormalGenerator::operator()()
{
    return m_dist(m_engine);
}