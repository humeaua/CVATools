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

namespace Maths
{
    class StatisticGatherer
    {
    public:
        virtual void DumpOneResult(double result) = 0;
        virtual Utilities::Matrix<double> GetResultsSoFar() const = 0;
        
        virtual StatisticGatherer * clone() const = 0;
        virtual ~StatisticGatherer();
    };
    
    class StatisticMean : public StatisticGatherer
    {
    public:
        StatisticMean();
        virtual void DumpOneResult(double result);
        virtual Utilities::Matrix<double> GetResultsSoFar() const;
        
        virtual StatisticGatherer * clone() const;
        virtual ~StatisticMean();
    protected:
        size_t m_PathsDone;
        double m_runningSum;
    };
}

#endif /* defined(__CVATools__StatisticGatherer__) */
