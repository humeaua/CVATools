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

template<class T>
class RandomNumberGeneratorBase
{
public:
    RandomNumberGeneratorBase()
    {}
    virtual ~RandomNumberGeneratorBase()
    {}
    
    virtual T operator()() = 0;
};

#endif /* defined(__CVATools__RandomNumberGeneratorBase__) */
