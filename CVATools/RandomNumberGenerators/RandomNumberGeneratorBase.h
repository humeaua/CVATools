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
#include "MCEngine.h"

class RandomNumberGeneratorBase
{
protected:
    std::tr1::shared_ptr<MCEngine> m_engine;
public:
    RandomNumberGeneratorBase(long long & m_seed);
    virtual ~RandomNumberGeneratorBase();
    
    virtual double operator()() const;
};

#endif /* defined(__CVATools__RandomNumberGeneratorBase__) */
