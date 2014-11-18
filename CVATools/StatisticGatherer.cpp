//
//  StatisticGatherer.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 03/05/14.
//
//

#include "StatisticGatherer.h"

namespace Maths
{
    StatisticGatherer::~StatisticGatherer()
    {}
    
    template<>
    double Statistic<MEAN>::GetResultsSoFar() const
    {
        return m_runningSum / m_PathsDone;
    }
    
    template<>
    double Statistic<STANDARD_DEVIATION>::GetResultsSoFar() const
    {
        const double average = m_runningSum / m_PathsDone;
        return m_SumOfSquares / m_PathsDone - average * average;
    }
}