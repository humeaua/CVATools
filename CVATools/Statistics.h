//
//  Statistics.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 16/06/13.
//
//

#ifndef __CVATools__Statistics__
#define __CVATools__Statistics__

#include <iostream>
#include <vector>

namespace Maths
{
    class Statistics
    {
    private:
        static std::size_t Partition(const std::vector<double> & dData, std::size_t iPivot);
    public:
        
        //  Method to compute the mean of data
        static double Mean(const std::vector<double> & dData);
        static double MeanOld(const std::vector<double> & dData);
        
        //  Method to compute the median of data
        static double Median(const std::vector<double> & dData);
        static double kthSmallest(const std::vector<double> & dData, std::size_t k);
        
        //  Method to compute the standard deviation of data
        static double StandardDeviation(const std::vector<double> & dData);
        static double StandardDeviationOld(const std::vector<double> & dData);
        
        //  Method to compute the variance of data
        static double Variance(const std::vector<double> & dData);
        static double VarianceOld(const std::vector<double> & dData);
        
        //  Rolling methods
        static std::vector<double> RollingAverage(const std::vector<double>& dData);
        static std::vector<double> RollingVariance(const std::vector<double>& dData);
        static std::vector<double> RollingStandardDeviation(const std::vector<double>& dData);
        
        //  Method to compute the Quantile of data
        static double Quantile(double dQuantile, const std::vector<double> & dData);
        
        //  Method to compute the empirical distribution of the Data given a fixed number of buckets
        static std::vector<std::pair<double,std::size_t> > EmpiricalDistribution(const std::vector<double> & dData, const std::size_t iNBuckets);
        
        //  Method to compute the empirical distribution of the data given fixed points
        static std::vector<std::pair<double,std::size_t> > EmpiricalDistribution(const std::vector<double> & dData, const std::vector<double> & dPoints);
    };
}

#endif /* defined(__CVATools__Statistics__) */
