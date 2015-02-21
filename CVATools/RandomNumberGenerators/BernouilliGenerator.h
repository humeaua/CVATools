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

class BernouilliGenerator : public RandomNumberGeneratorBase
{
protected:
    std::tr1::bernoulli_distribution m_dist;
    std::tr1::minstd_rand0 m_engine;
    
public:
    BernouilliGenerator(long long & seed, const double & p);
    
    double operator()();
};

#endif /* defined(__CVATools__BernouilliGenerator__) */
