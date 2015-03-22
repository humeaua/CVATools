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
    std::vector<double>::const_iterator it = std::lower_bound(cum_proba.begin(), cum_proba.end(), uniform);
    if (it != cum_proba.end())
    {
        return x[std::distance(it, cum_proba.begin())];
    }
    else
    {
        return x.back();
    }
}

template<class T>
class DiscreteGenerator : public RandomNumberGeneratorBase<T>
{
    std::tr1::random_device                  m_rand_dev;
    std::tr1::mt19937                        m_generator;
    std::tr1::normal_distribution<double> m_unif;
    std::vector<T> m_x;
    std::vector<double> m_cumProba;
public:
    DiscreteGenerator(const std::vector<T> & x, const std::vector<double> & proba, long long & seed)
    : m_generator(seed), m_unif(0.0,1.0), m_x(x)
    {
        double cum_sum = 0;
        for (size_t i = 0 ; i < proba.size() ; ++i)
        {
            cum_sum += proba[i];
            m_cumProba[i] = cum_sum;
        }
    }
    
    T operator()()
    {
        const double unif = m_generator(m_unif);
        return Generate(unif, m_cumProba, m_x);
    }
};

#endif /* defined(__CVATools__DiscreteGenerator__) */
