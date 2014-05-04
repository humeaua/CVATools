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
    
    StatisticMean::StatisticMean() : m_PathsDone(0), m_runningSum(0.0)
    {}
    
    void StatisticMean::DumpOneResult(double result)
    {
        m_runningSum += result;
        m_PathsDone++;
    }
    
    StatisticGatherer * StatisticMean::clone() const
    {
        return new StatisticMean(*this);
    }
    
    StatisticMean::~StatisticMean()
    {}
    
    Utilities::Matrix<double> StatisticMean::GetResultsSoFar() const
    {
        Utilities::Matrix<double> res(1,1);
        res[0][0] = m_runningSum / m_PathsDone;
        return res;
    }
}