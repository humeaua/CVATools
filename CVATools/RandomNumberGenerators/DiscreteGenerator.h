//
//  DiscreteGenerator.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 19/03/15.
//
//

#ifndef __CVATools__DiscreteGenerator__
#define __CVATools__DiscreteGenerator__

#include <iostream>
#include "RandomNumberGeneratorBase.h"
#include <tr1/random>
#include <vector>
#include <algorithm>
#include "Exception.h"

template<class T>
const T & Generate(const double & uniform, const std::vector<double> & cum_proba, const std::vector<T> & x)
{
    if (cum_proba.size() == 0)
    {
        throw EXCEPTION("cum_proba is empty");
    }
    if (x.size() == 0)
    {
        throw EXCEPTION("x is empty");
    }
    if (x.size() != cum_proba.size())
    {
        throw EXCEPTION("cum_proba and x must be the same size");
    }
    if (uniform < cum_proba.front())
    {
        return x.front();
    }
    for (size_t i = 0 ; i < cum_proba.size()-1 ; ++i)
    {
        if (uniform > cum_proba[i] && uniform <= cum_proba[i+1])
        {
            return x[i+1];
        }
    }
    throw EXCEPTION("Not found!");
}

template<class T>
class DiscreteGenerator : public RandomNumberGeneratorBase<T>
{
    std::vector<T> m_x;
    std::vector<double> m_cumProba;
public:
    DiscreteGenerator(const std::vector<T> & x, const std::vector<double> & proba, unsigned int & seed)
    :  m_x(x), m_cumProba(proba.size())
    {
        double cum_sum = 0;
        for (size_t i = 0 ; i < proba.size() ; ++i)
        {
            cum_sum += proba[i];
            m_cumProba[i] = cum_sum;
        }
        srand(seed);
    }
    
    T operator()()
    {
        const double unif = static_cast<double>(rand()) / RAND_MAX;
        return Generate(unif, m_cumProba, m_x);
    }
};

#endif /* defined(__CVATools__DiscreteGenerator__) */
