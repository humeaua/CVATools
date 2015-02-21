//
//  RandomNumberGeneratorBase.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 21/02/15.
//
//

#ifndef __CVATools__RandomNumberGeneratorBase__
#define __CVATools__RandomNumberGeneratorBase__

#include <iostream>
#include <tr1/memory>

class RandomNumberGeneratorBase
{
protected:
    long long m_seed;
public:
    RandomNumberGeneratorBase(long long & m_seed);
    virtual ~RandomNumberGeneratorBase();
    
    virtual double operator()() = 0;
};

#endif /* defined(__CVATools__RandomNumberGeneratorBase__) */
