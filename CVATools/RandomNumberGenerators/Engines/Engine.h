//
//  Engine.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 28/02/15.
//
//

#ifndef __CVATools__Engine__
#define __CVATools__Engine__

#include <iostream>

//////////////////////////////////////////////////
///
///     Base class for Engine
///
//////////////////////////////////////////////////
template <class T>
class Engine
{
protected:
    T m_engine;
    long long & m_seed;
public:
    Engine(long long & seed) : m_seed(seed)
    {
        m_engine.seed(seed);
    }
    
    ~Engine()
    {}
    
    double operator()()
    {
        return m_engine();
    }
    
    double min() const
    {
        return m_engine.min();
    }
    
    double max() const
    {
        return m_engine.max();
    }
};

#endif /* defined(__CVATools__EngineBase__) */
