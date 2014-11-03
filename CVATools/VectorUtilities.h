//
//  VectorUtilities.h
//  Seminaire
//
//  Created by Alexandre HUMEAU on 19/04/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Seminaire_VectorUtilities_h
#define Seminaire_VectorUtilities_h

#include <vector>
#include <algorithm>
#include <cmath>
#include "Require.h"
#include <numeric>

namespace Utilities {
    
    template<class T>
    inline int FindInVector(const std::vector<T> & vect, T value, bool bSort = false)
    {
        std::vector<T> copy = vect;
        
        if (bSort)
        {
            std::sort(copy.begin(), copy.end());
        }
        for (std::size_t i = 0 ; i < copy.size() - 1 ; ++i)
        {
            if ((value >= copy.at(i)) && (value < copy.at(i + 1)))
            {
                return static_cast<int>(i);
			}
        }
        if (value == copy.back())
        {
            return static_cast<int>(copy.size() - 1);
        }
        return -1;
    };
    
    template <class T, class U>
    const T& get(const std::vector<T>& v,
          size_t i,
          const U& defaultValue)
    {
        if (v.empty()) 
        {
            return defaultValue;
        }
        else if (i < v.size()) 
        {
            return v.at(i);
        }
        else 
        {
            return v.back();
        }
    };
    
    template<class T, class U>
    std::pair<std::vector<T>, std::vector<U> > GetPairOfVectorFromVectorOfPair(const std::vector<std::pair<T, U> > & VectorOfPair)
    {
        std::pair<std::vector<T>, std::vector<U> > PairOfVector;
        
        for (std::size_t i = 0 ; i < VectorOfPair.size() ; ++i)
        {
            PairOfVector.first.push_back(VectorOfPair.at(i).first);
            PairOfVector.second.push_back(VectorOfPair.at(i).second);
        }
        return PairOfVector;
    };
    
    template<class T> bool IsFound(const std::vector<T> & vect, const T & value, int & iWhere)
    {
        //  Check if the value is in the vector
        for (std::size_t i = 0 ; i < vect.size(); ++i)
        {
            if (vect.at(i) == value)
            {
                iWhere = static_cast<int>(i);
                return true;
            }
        }
        //  If not found return the size of the vector
        iWhere = static_cast<int>(vect.size());
        return false;
    };
    
    template<>
    inline bool IsFound(const std::vector<double> & vect, const double& value, int & iWhere)
    {
        const double dTolerance = 1e-10;
        for (std::size_t i = 0 ; i < vect.size(); ++i)
        {
            if (std::abs(vect.at(i) - value) < dTolerance)
            {
                iWhere = static_cast<int>(i);
                return true;
            }
        }
        //  If not found return the size of the vector
        iWhere = static_cast<int>(vect.size());
        return false;
    }
    
    // May change this function to a template version
    template<typename T>
    bool AreEqual(const std::vector<T> & vect1, const std::vector<T> & vect2, T tolerance)
    {
        if (vect1.size() != vect2.size())
            return false;
        
        for (std::size_t i = 0 ; i < vect1.size() ; ++i)
        {
            if (std::abs(vect1.at(i) - vect2.at(i)) > tolerance)
            {
                return false;
            }
        }
        return true;
    }
    
    template<class T> std::vector<T> Subset(const std::vector<T> & vect, std::size_t iBegin, std::size_t iEnd)
    {
        std::size_t iN = vect.size();
        REQUIREEXCEPTION(iBegin < iN, "Begin is out of the data");
        REQUIREEXCEPTION(iEnd < iN, "End is out of the data");
        REQUIREEXCEPTION(iBegin <= iEnd, "End is before beginning of data");
        
        std::vector<T> result;
        for (std::size_t i = iBegin ; i <= iEnd ; ++i)
        {
            result.push_back(vect.at(i));
        }
        return result;
    }
    
    //  Function to get a pointer from a vector
    //  If vector is empty, the function returns a NULL pointer
    //  Else it returns the address of the first element of the vector
    template<typename T> T* GetPointer(std::vector<T> & vect)
    {
        if (vect.empty())
        {
            return NULL;
        }
        else
        {
            return &(vect.at(0));
        }
    }

    //  Function to get the index of a variable in a vector
    //  Return -1 if not found
    template<typename T> int GetIndex(const std::vector<T> & vect, const T & value)
    {
        typename std::vector<T>::const_iterator it = std::find(vect.begin(), vect.end(), value);
        if (it != vect.end() || (it == vect.end() && value == vect.back()))
        {
            return static_cast<int>(it - vect.begin());
        }
        else
        {
            return -1;
        }
    }

    //  Function to return the norm2 of a vector
    template <typename T>
    T norm_2(const std::vector<T> & vect)
    {
        return sqrt(std::inner_product(vect.begin(), vect.end(), vect.begin(), 0.0));
    }
    
    template <typename T>
    std::vector<T> Diff(const std::vector<T> & vect1, const std::vector<T> & vect2)
    {
        REQUIREEXCEPTION(vect1.size() == vect2.size(), "Cannot compute diff, vectors do not have same size");
        std::vector<T> result(vect1.size());
        
        std::transform(vect1.begin(), vect1.end(), vect2.begin(), std::back_inserter(result), std::minus<T>());
        return result;
    }
    
    //  Function to return the mean of a vector
    template<typename InputType, typename ReturnType>
    ReturnType Mean(const std::vector<InputType> & vect)
    {
        REQUIREEXCEPTION(vect.size() > 0, "Size of vector is 0");
        return (ReturnType)(std::accumulate(vect.begin(), vect.end(), 0.0)) / vect.size();
    }
    
    //  Function to return the mean of a vector
    template<typename InputType, typename ReturnType>
    ReturnType Variance(const std::vector<InputType> & vect)
    {
        REQUIREEXCEPTION(vect.size() > 1, "Size of vector must be above 1");
        std::size_t size = vect.size();
        ReturnType mean = Mean<InputType, ReturnType>(vect);
        return (ReturnType)(std::inner_product(vect.begin(), vect.end(), vect.begin(), 0.0)) / (size - 1) - mean * mean * size / (size - 1);
    }
    
    //  Function to return the mean of a vector
    template<typename InputType, typename ReturnType>
    ReturnType StdDev(const std::vector<InputType> & vect)
    {
        return sqrt(Variance<InputType, ReturnType>(vect));
    }
    
    inline bool Pair1stLowerOrEqual(const std::pair<double, double> & lhs, const std::pair<double, double> & rhs)
    {
        return lhs.first < rhs.first;
    }
};

#endif
