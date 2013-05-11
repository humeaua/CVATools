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
            if ((value >= copy[i]) && (value < copy[i + 1])) {
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
    T get(const std::vector<T>& v,
          size_t i,
          U& defaultValue)
    {
        if (v.empty()) 
        {
            return defaultValue;
        }
        else if (i < v.size()) 
        {
            return v[i];
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
            PairOfVector.first.push_back(VectorOfPair[i].first);
            PairOfVector.second.push_back(VectorOfPair[i].second);
        }
        return PairOfVector;
    };
    
    template<class T> bool IsFound(const std::vector<T> & vect, T & value, std::size_t * iWhere)
    {
        //  Check if the value is in the vector
        for (std::size_t i = 0 ; i < vect.size(); ++i)
        {
            if (vect[i] == value)
            {
                *iWhere = i;
                return true;
            }
        }
        //  If not found return the size of the vector
        *iWhere = vect.size();
        return false;
    };
    
    // May change this function to a template version
    bool AreEqual(const std::vector<double> & vect1, const std::vector<double> & vect2, double tolerance);
    
};

#endif
