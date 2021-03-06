//
//  Statistics.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 16/06/13.
//
//

#include "Statistics.h"
#include <cmath>
#include <numeric>
#include "Require.h"
#include <algorithm>
#include "VectorUtilities.h"

namespace Maths
{
    double Statistics::Mean(const std::vector<double> &dData)
    {
        return dData.size() == 0 ? 0.0 : std::accumulate(dData.begin(), dData.end(), 0.0)/ dData.size();
    }
    
    double Statistics::MeanOld(const std::vector<double> &dData)
    {
        std::size_t n = dData.size();
        double dResult = 0.0;
        
        for (std::size_t i = 0 ; i < n ; ++i)
        {
            dResult += dData.at(i);
        }
        
        if (n == 0)
        {
            return 0.0;
        }
        else
        {
            return dResult / n;
        }
    }
    
    double Statistics::Median(const std::vector<double> &dData)
    {
        std::size_t iN = dData.size(), nOver2 = iN / 2;
        if (iN % 2)
        {
            return kthSmallest(dData, nOver2);
        }
        else
        {
            return 0.5 * (kthSmallest(dData, nOver2) + kthSmallest(dData, nOver2 - 1));
        }
    }
    
    std::size_t Statistics::Partition(const std::vector<double> &dData, std::size_t iPivot)
    {
        /*
         function partition(list, left, right, pivotIndex)
         pivotValue := list[pivotIndex]
         swap list[pivotIndex] and list[right]  // Move pivot to end
         storeIndex := left
         for i from left to right-1
         if list[i] < pivotValue
         swap list[storeIndex] and list[i]
         increment storeIndex
         swap list[right] and list[storeIndex]  // Move pivot to its final place
         return storeIndex
         */
        
        REQUIREEXCEPTION(iPivot < dData.size(), "Pivot is over the size of the data");
        double dPivotValue = dData.at(iPivot);
        std::size_t iN = dData.size();
        std::vector<double> dCopy = dData;
        
        std::swap(dCopy[iPivot], dCopy.back());
        
        std::size_t iStoreIndex = 0;
        
        for (std::size_t i = 0 ; i < iN ; ++i)
        {
            if (dData.at(i) < dPivotValue)
            {
                std::swap(dCopy.at(iStoreIndex), dCopy.at(i));
                iStoreIndex++;
            }
            std::swap(dCopy.back(), dCopy.at(iStoreIndex));
        }
        return iStoreIndex;
    }
    
    double Statistics::kthSmallest(const std::vector<double> &dData, std::size_t k)
    {
        /*
         // Returns the k-th smallest element of list within left..right inclusive.
         function select(list, left, right, k)
         if left = right        // If the list contains only one element
         return list[left]  // Return that element
         pivotIndex := ...     // select a pivotIndex between left and right
         pivotNewIndex := partition(list, left, right, pivotIndex)
         pivotDist := pivotNewIndex - left + 1
         // The pivot is in its final sorted position,
         // so pivotDist reflects its 1-based position if list were sorted
         if pivotDist = k
         return list[pivotNewIndex]
         else if k < pivotDist
         return select(list, left, pivotNewIndex - 1, k)
         else
         return select(list, pivotNewIndex + 1, right, k - pivotDist)
         */
        std::size_t iN = dData.size();
        if (iN == 1)
        {
            return dData.back();
        }
        std::size_t iPivotIndex = iN / 2;
        std::size_t iPivotNewIndex = Partition(dData, iPivotIndex), iPivotDist = iPivotNewIndex + 1;
        
        if (iPivotDist == k)
        {
            return dData[k];
        }
        else if (k < iPivotDist)
        {
            std::vector<double> dNewData = Utilities::Subset(dData, 0, iPivotNewIndex - 1);
            return kthSmallest(dNewData, k);
        }
        else
        {
            std::vector<double> dNewData = Utilities::Subset(dData, iPivotNewIndex + 1, iN - 1);
            return kthSmallest(dNewData, k - iPivotDist);
        }
    }
    
    double Statistics::Variance(const std::vector<double> &v)
    {
        size_t size = v.size();
        double mean = Mean(v);
        if (size <= 1)
        {
            return 0.0;
        }
        else
        {
            return std::inner_product(v.begin(), v.end(), v.begin(), 0.0) / (size - 1) - mean * mean * size / (size - 1);
        }
    }
    
    double Statistics::VarianceOld(const std::vector<double> &v)
    {
        std::size_t n = v.size();
        double dMean = 0.0, dVariance = 0.0, dElementLoc;
        for (std::size_t i = 0 ; i < n ; ++i)
        {
            dElementLoc = v.at(i);
            dMean += dElementLoc;
            dVariance += dElementLoc * dElementLoc;
        }
        dMean /= n;
        dVariance /= n;
        dVariance -= dMean * dMean;
        return n <= 1 ? 0.0 : dVariance;
    }
    
    double Statistics::StandardDeviation(const std::vector<double> &dData)
    {
        return sqrt(Variance(dData));
    }
    
    double Statistics::StandardDeviationOld(const std::vector<double> &dData)
    {
        return sqrt(VarianceOld(dData));
    }
    
    std::vector<double> Statistics::RollingAverage(const std::vector<double>& dData)
    {
        std::size_t iN = dData.size();
        std::vector<double> dResults(iN);
        dResults.at(0) = dData.at(0);
        
        for (std::size_t i = 1 ; i < iN ; ++i)
        {
            dResults.at(i) = 1.0 / (i + 1.0) * dData.at(i) + i / (i + 1.0) * dResults.at(i - 1);
        }
        return dResults;
    }
    
    std::vector<double> Statistics::RollingVariance(const std::vector<double>& dData)
    {
        std::size_t iN = dData.size();
        std::vector<double> dResults(iN);
        double dMean = dData[0];
        dResults[0] = 0;
        
        for (std::size_t i = 1 ; i < iN ; ++i)
        {
            dMean = 1.0 / (i + 1.0) * dData.at(i) + i / (i + 1.0) * dMean;
            dResults.at(i) = dResults.at(i-1) + (dData.at(i) - dMean) * (dData.at(i) - dMean);
        }
        return dResults;
    }
    
    std::vector<double> Statistics::RollingStandardDeviation(const std::vector<double>& dData)
    {
        std::size_t iN = dData.size();
        std::vector<double> dResults(iN);
        double dMean = dData.at(0);
        dResults.at(0) = 0;
        
        for (std::size_t i = 1 ; i < iN ; ++i)
        {
            dMean = 1.0 / (i + 1.0) * dData.at(i) + i / (i + 1.0) * dMean;
            dResults.at(i) = dResults[i - 1] * dResults.at(i-1) + (dData.at(i) - dMean) * (dData.at(i) - dMean);
            dResults.at(i) = sqrt(dResults.at(i));
        }
        return dResults;
    }
    
    double Statistics::Quantile(double dQuantile, const std::vector<double> &dData)
    {
        std::vector<double> dDataCopy = dData;
        std::sort(dDataCopy.begin(), dDataCopy.end());
        if (dQuantile < 0.0 || dQuantile > 1.0)
        {
            if (dQuantile == 1.0 || dQuantile == 0.0)
            {
                return dQuantile == 0.0 ? dDataCopy.at(0) : dDataCopy.back();
            }
            std::size_t iNElmts = dDataCopy.size(), iElmtQuantile = (std::size_t)floor(dQuantile * iNElmts);
            double dElmtQuantile = dQuantile * iNElmts - iElmtQuantile;
            
            return dElmtQuantile * dDataCopy.at(iElmtQuantile) + (1 - dElmtQuantile) * dDataCopy.at(iElmtQuantile + 1);
        }
        else
        {
            return 0.0;
        }
    }
    
    std::vector<std::pair<double, std::size_t> > Statistics::EmpiricalDistribution(const std::vector<double> &dData, const std::size_t iNBuckets)
    {
        std::vector<double> dDataCopy = dData;
        std::vector<std::pair<double, std::size_t> > dResults(iNBuckets);
        std::sort(dDataCopy.begin(), dDataCopy.end());
        
        double dMin = dDataCopy.at(0), dMax = dDataCopy.back();
        double h = (dMax - dMin) / iNBuckets;
        
        std::size_t iBucketBeginNew = 0;
        
        for (std::size_t iBucket = 0 ; iBucket < iNBuckets ; ++iBucket)
        {
            dResults.at(iBucket).first = dMin + iBucket * h;
        }
        
        for (std::size_t iPoint = 0 ; iPoint < dDataCopy.size() - 1 ; ++iPoint)
        {
            for (std::size_t iBucket = iBucketBeginNew ; iBucket < iNBuckets ; ++iBucket)
            {
                if (dDataCopy.at(iPoint) >= dMin + iBucket * h && dDataCopy.at(iPoint) < dMin + (iBucket + 1) * h)
                {
                    dResults.at(iBucket).second++;
                    //  We can restrict the search to the last bucket since the vector in sorted
                    iBucketBeginNew = iBucket;
                    break;
                }
            }
        }
        dResults.back().second++;
        
        return dResults;
    }
    
    std::vector<std::pair<double, std::size_t> > Statistics::EmpiricalDistribution(const std::vector<double> & dData, const std::vector<double> & dPoints)
    {
        std::vector<double> dDataCopy = dData;
        std::size_t iNBuckets = dPoints.size();
        std::vector<std::pair<double, std::size_t> > dResults(iNBuckets);
        std::sort(dDataCopy.begin(), dDataCopy.end());
        
        std::size_t iBucketBeginNew = 0;
        
        for (std::size_t iBucket = 0 ; iBucket < iNBuckets ; ++iBucket)
        {
            dResults.at(iBucket).first = dPoints.at(iBucket);
        }
        
        for (std::size_t iPoint = 0 ; iPoint < dDataCopy.size() - 1 ; ++iPoint)
        {
            for (std::size_t iBucket = iBucketBeginNew ; iBucket < iNBuckets - 1 ; ++iBucket)
            {
                if (dDataCopy.at(iPoint) >= dPoints.at(iBucket) && dDataCopy.at(iPoint) < dPoints.at(iBucket + 1))
                {
                    dResults.at(iBucket).second++;
                    //  We can restrict the search to the last bucket since the vector in sorted
                    iBucketBeginNew = iBucket;
                    break;
                }
            }
        }
        
        return dResults;
    }
}