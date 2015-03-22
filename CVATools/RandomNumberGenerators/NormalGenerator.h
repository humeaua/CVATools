//
//  NormalGenerator.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 28/02/15.
//
//

#ifndef __CVATools__NormalGenerator__
#define __CVATools__NormalGenerator__

#include <iostream>
#include <tr1/random>
#include "Engines/Engine.h"
#include "RandomNumberGeneratorBase.h"

template<class T>
class NormalGenerator : public RandomNumberGeneratorBase<T>
{
protected:
    std::tr1::normal_distribution<T> m_dist;
    Engine<std::tr1::ranlux64_base_01> m_engine;
    
public:
    NormalGenerator(long long & seed, const double & mean, const double & stdev) : m_engine(seed), m_dist(mean, stdev)
    {}
    
    T operator()()
    {
        return m_dist(m_engine);
    }
};

#endif /* defined(__CVATools__NormalGenerator__) */
