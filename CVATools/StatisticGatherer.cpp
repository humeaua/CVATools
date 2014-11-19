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
    
    template<>
    double Statistic<MIN>::GetResultsSoFar() const
    {
        return m_runningSum;
    }
    
    template<>
    double Statistic<MAX>::GetResultsSoFar() const
    {
        return m_runningSum;
    }
    
    template<>
    void Statistic<STANDARD_DEVIATION>::DumpOneResult(double result)
    {
        m_runningSum += result;
        m_SumOfSquares += result * result;
        m_PathsDone++;
    }
    
    template<>
    void Statistic<MEAN>::DumpOneResult(double result)
    {
        m_runningSum += result;
        m_PathsDone++;
    }
    
    template<>
    void Statistic<MIN>::DumpOneResult(double result)
    {
        m_runningSum = std::min(m_runningSum, result);
        m_PathsDone++;
    }
    
    template<>
    void Statistic<MAX>::DumpOneResult(double result)
    {
        m_runningSum = std::max(m_runningSum, result);
        m_PathsDone++;
    }
}