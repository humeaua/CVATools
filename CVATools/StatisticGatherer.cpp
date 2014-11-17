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
    Utilities::Matrix<double> Statistic<MEAN>::GetResultsSoFar() const
    {
        Utilities::Matrix<double> res(1,1);
        res(0,0) = m_runningSum / m_PathsDone;
        return res;
    }
    
    template<>
    Utilities::Matrix<double> Statistic<STANDARD_DEVIATION>::GetResultsSoFar() const
    {
        Utilities::Matrix<double> res(1,1);
        const double average = m_runningSum / m_PathsDone;
        res(0,0) = m_SumOfSquares / m_PathsDone - average * average;
        return res;
    }
}