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

class Statistics
{
public:
    Statistics();
    virtual ~Statistics();
    
    //  Method to compute the mean of data
    virtual double Mean(const std::vector<double> & dData) const;
    
    //  Method to compute the median of data
    virtual double Median(const std::vector<double> & dData) const;
    
    //  Method to compute the standard deviation of data
    virtual double StandardDeviation(const std::vector<double> & dData) const;
    
    //  Method to compute the variance of data
    virtual double Variance(const std::vector<double> & dData) const;
    
    //  Method to compute the Quantile of data
    virtual double Quantile(double dQuantile, const std::vector<double> & dData) const;
    
    //  Method to compute the empirical distribution of the Data given a fixed number of buckets
    virtual std::vector<std::pair<double,std::size_t> > EmpiricalDistribution(const std::vector<double> & dData, const std::size_t iNBuckets) const;
    
    //  Method to compute the empirical distribution of the data given fixed points
    virtual std::vector<std::pair<double,std::size_t> > EmpiricalDistribution(const std::vector<double> & dData, const std::vector<double> & dPoints) const;
};

#endif /* defined(__CVATools__Statistics__) */
