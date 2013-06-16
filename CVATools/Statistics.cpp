//
//  Statistics.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 16/06/13.
//
//

#include "Statistics.h"
#include <cmath>

Statistics::Statistics()
{}

Statistics::~Statistics()
{}

double Statistics::Mean(const std::vector<double> &dData) const
{
    double dMean = 0.0;
    std::size_t n = dData.size();
    for (std::size_t i = 0 ; i < n ; ++i)
    {
        dMean += dData[i];
    }
    return n != 0 ? dMean / n : 0.0;
}

double Statistics::Median(const std::vector<double> &dData) const
{
    std::size_t n = dData.size();
    std::vector<double> dDataCopy = dData;
    std::sort(dDataCopy.begin(), dDataCopy.end());
    
    return n % 2 == 1 ? dDataCopy[n / 2] : 0.5 * (dDataCopy[n/2 - 1] + dDataCopy[n/2]);
}

double Statistics::Variance(const std::vector<double> &dData) const
{
    double dVariance = 0.0, dMean = 0.0;
    for (std::size_t i = 0 ; i < dData.size() ; ++i)
    {
        dMean += dData[i];
        dVariance += dData[i] * dData[i];
    }
    dMean /= dData.size();
    return dVariance / dData.size() - dMean * dMean;
}

double Statistics::StandardDeviation(const std::vector<double> &dData) const
{
    return sqrt(Variance(dData));
}

double Statistics::Quantile(double dQuantile, const std::vector<double> &dData) const
{
    std::vector<double> dDataCopy = dData;
    std::sort(dDataCopy.begin(), dDataCopy.end());
    if (dQuantile < 0.0 || dQuantile > 1.0)
    {
        if (dQuantile == 1.0 || dQuantile == 0.0)
        {
            return dQuantile == 0.0 ? dDataCopy[0] : dDataCopy.back();
        }
        std::size_t iNElmts = dDataCopy.size(), iElmtQuantile = (std::size_t)floor(dQuantile * iNElmts);
        double dElmtQuantile = dQuantile * iNElmts - iElmtQuantile;
        
        return dElmtQuantile * dDataCopy[iElmtQuantile] + (1 - dElmtQuantile) * dDataCopy[iElmtQuantile + 1];
    }
    else
    {
        return 0.0;
    }
}

std::vector<std::pair<double, std::size_t> > Statistics::EmpiricalDistribution(const std::vector<double> &dData, const std::size_t iNBuckets) const
{
    std::vector<double> dDataCopy = dData;
    std::vector<std::pair<double, std::size_t> > dResults(iNBuckets);
    std::sort(dDataCopy.begin(), dDataCopy.end());
    
    double dMin = dDataCopy[0], dMax = dDataCopy.back();
    double h = (dMax - dMin) / iNBuckets;
    
    std::size_t iBucketBeginNew = 0;
    
    for (std::size_t iBucket = 0 ; iBucket < iNBuckets ; ++iBucket)
    {
        dResults[iBucket].first = dMin + iBucket * h;
    }
    
    for (std::size_t iPoint = 0 ; iPoint < dDataCopy.size() - 1 ; ++iPoint)
    {
        for (std::size_t iBucket = iBucketBeginNew ; iBucket < iNBuckets ; ++iBucket)
        {
            if (dDataCopy[iPoint] >= dMin + iBucket * h && dDataCopy[iPoint] < dMin + (iBucket + 1) * h)
            {
                dResults[iBucket].second++;
                //  We can restrict the search to the last bucket since the vector in sorted
                iBucketBeginNew = iBucket;
                break;
            }
        }
    }
    dResults.back().second++;
    
    return dResults;
}

std::vector<std::pair<double, std::size_t> > Statistics::EmpiricalDistribution(const std::vector<double> & dData, const std::vector<double> & dPoints) const
{
    std::vector<double> dDataCopy = dData;
    std::size_t iNBuckets = dPoints.size();
    std::vector<std::pair<double, std::size_t> > dResults(iNBuckets);
    std::sort(dDataCopy.begin(), dDataCopy.end());
    
    std::size_t iBucketBeginNew = 0;
    
    for (std::size_t iBucket = 0 ; iBucket < iNBuckets ; ++iBucket)
    {
        dResults[iBucket].first = dPoints[iBucket];
    }
    
    for (std::size_t iPoint = 0 ; iPoint < dDataCopy.size() - 1 ; ++iPoint)
    {
        for (std::size_t iBucket = iBucketBeginNew ; iBucket < iNBuckets - 1 ; ++iBucket)
        {
            if (dDataCopy[iPoint] >= dPoints[iBucket] && dDataCopy[iPoint] < dPoints[iBucket + 1])
            {
                dResults[iBucket].second++;
                //  We can restrict the search to the last bucket since the vector in sorted
                iBucketBeginNew = iBucket;
                break;
            }
        }
    }
    
    return dResults;
}
