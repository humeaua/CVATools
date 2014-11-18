//
//  StatisticGatherer.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 03/05/14.
//
//

#ifndef __CVATools__StatisticGatherer__
#define __CVATools__StatisticGatherer__

#include <iostream>
#include "Matrix.h"
#include <cmath>

namespace Maths
{
    enum StatisticType
    {
        MEAN,
        STANDARD_DEVIATION
    };
    
    class StatisticGatherer
    {
    public:
        virtual void DumpOneResult(double result) = 0;
        virtual double GetResultsSoFar() const = 0;
        
        virtual StatisticGatherer * clone() const = 0;
        virtual ~StatisticGatherer();
    };
    
    template<StatisticType stat>
    class Statistic : public StatisticGatherer
    {
    public:
        Statistic() : m_PathsDone(0), m_runningSum(0.0), m_SumOfSquares(0.0)
        {}
        double GetResultsSoFar() const;
        
        void DumpOneResult(double result)
        {
            m_runningSum += result;
            m_SumOfSquares += result * result;
            m_PathsDone++;
        }
        
        StatisticGatherer * clone() const
        {
            return new Statistic(*this);
        }
        
        ~Statistic()
        {}
    protected:
        size_t m_PathsDone;
        double m_runningSum, m_SumOfSquares;
    };
    
    template<int power>
    class Moment : public StatisticGatherer
    {
    public:
        Moment() : m_PathsDone(0), m_runningSum(0)
        {}
        
        double GetResultsSoFar() const
        {
            return m_runningSum / m_PathsDone;
        }
        
        StatisticGatherer * clone() const
        {
            return new Moment(*this);
        }
        
        void DumpOneResult(double result)
        {
            m_runningSum += pow(result, power);
            m_PathsDone++;
        }
        
        ~Moment()
        {}
        
    protected:
        size_t m_PathsDone;
        double m_runningSum;
    };
}

#endif /* defined(__CVATools__StatisticGatherer__) */
