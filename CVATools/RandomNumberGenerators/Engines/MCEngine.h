//
//  MCEngine.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 21/02/15.
//
//

#ifndef __CVATools__MCEngine__
#define __CVATools__MCEngine__

#include <iostream>

class MCEngine
{
protected:
    long long m_seed;
public:
    MCEngine(long long & seed);
    virtual ~MCEngine();
    
    virtual double operator()() const = 0;
};

#endif /* defined(__CVATools__MCEngine__) */
