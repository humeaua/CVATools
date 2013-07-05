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
    Statistics::Statistics()
    {}
    
    Statistics::~Statistics()
    {}
    
    double Statistics::Mean(const std::vector<double> &dData) const
    {
        std::size_t n = dData.size();
        return n == 0 ? 0.0 : std::accumulate(dData.begin(), dData.end(), 0.0)/ n;
    }
    
    double Statistics::MeanOld(const std::vector<double> &dData) const
    {
        std::size_t n = dData.size();
        double dResult = 0.0;
        
        for (std::size_t i = 0 ; i < n ; ++i)
        {
            dResult += dData[i];
        }
        return n == 0 ? 0.0 : dResult / n;
    }
    
    double Statistics::Median(const std::vector<double> &dData) const
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
    
    std::size_t Statistics::Partition(const std::vector<double> &dData, std::size_t iPivot) const
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
        
        Utilities::requireException(iPivot < dData.size(), "Pivot is over the size of the data");
        double dPivotValue = dData[iPivot];
        std::size_t iN = dData.size();
        std::vector<double> dCopy = dData;
        
        std::swap(dCopy[iPivot], dCopy.back());
        
        std::size_t iStoreIndex = 0;
        
        for (std::size_t i = 0 ; i < iN ; ++i)
        {
            if (dData[i] < dPivotValue)
            {
                std::swap(dCopy[iStoreIndex], dCopy[i]);
                iStoreIndex++;
            }
            std::swap(dCopy.back(), dCopy[iStoreIndex]);
        }
        return iStoreIndex;
    }
    
    double Statistics::kthSmallest(const std::vector<double> &dData, std::size_t k) const
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
            return dData.back();
        std::size_t iPivotIndex = iN / 2;
        std::size_t iPivotNewIndex = Partition(dData, iPivotIndex), iPivotDist = iPivotNewIndex + 1;
        
        if (iPivotDist == k)
            return dData[k];
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
    
    double Statistics::Variance(const std::vector<double> &v) const
    {
        double mean = Mean(v);
        std::vector<double> diff(v.size());
        std::transform(v.begin(), v.end(), diff.begin(),
                       std::bind2nd(std::minus<double>(), mean));
        return v.size() == 0 ? 0.0 : std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0) / v.size();
    }
    
    double Statistics::VarianceOld(const std::vector<double> &v) const
    {
        std::size_t n = v.size();
        double dMean = 0.0, dVariance = 0.0, dElementLoc;
        for (std::size_t i = 0 ; i < n ; ++i)
        {
            dElementLoc = v[i];
            dMean += dElementLoc;
            dVariance += dElementLoc * dElementLoc;
        }
        dMean /= n;
        dVariance /= n;
        dVariance -= dMean * dMean;
        return n == 0 ? 0.0 : dVariance;
    }
    
    double Statistics::StandardDeviation(const std::vector<double> &dData) const
    {
        return sqrt(Variance(dData));
    }
    
    double Statistics::StandardDeviationOld(const std::vector<double> &dData) const
    {
        return sqrt(VarianceOld(dData));
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
}