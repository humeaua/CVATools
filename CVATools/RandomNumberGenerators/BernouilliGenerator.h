//
//  BernouilliGenerator.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 21/02/15.
//
//

#ifndef __CVATools__BernouilliGenerator__
#define __CVATools__BernouilliGenerator__

#include <iostream>
#include "RandomNumberGeneratorBase.h"
#include <tr1/random>
#include "Engines/Engine.h"

class BernouilliGenerator : public RandomNumberGeneratorBase<double>
{
protected:
    std::tr1::bernoulli_distribution m_dist;
    Engine<std::tr1::minstd_rand> m_engine;
    
public:
    BernouilliGenerator(long long & seed, const double & p);
    
    double operator()();
};

#endif /* defined(__CVATools__BernouilliGenerator__) */
