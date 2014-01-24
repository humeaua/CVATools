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
            if ((value >= copy.at(i)) && (value < copy.at(i + 1))) {
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
    
    template<class T> bool IsFound(const std::vector<T> & vect, T & value, std::size_t & iWhere)
    {
        //  Check if the value is in the vector
        for (std::size_t i = 0 ; i < vect.size(); ++i)
        {
            if (vect.at(i) == value)
            {
                iWhere = i;
                return true;
            }
        }
        //  If not found return the size of the vector
        iWhere = vect.size();
        return false;
    };
    
    // May change this function to a template version
    template<typename T>
    bool AreEqual(const std::vector<T> & vect1, const std::vector<T> & vect2, T tolerance)
    {
        if (vect1.size() != vect2.size())
            return false;
        
        for (std::size_t i = 0 ; i < vect1.size() ; ++i)
        {
            if (fabs(vect1.at(i) - vect2.at(i)) > tolerance)
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
            return NULL;
        else
            return &(vect.at(0));
    }

    //  Function to get the index of a variable in a vector
    //  Return -1 if not found
    template<typename T> std::size_t GetIndex(const std::vector<T> & vect, const T & value)
    {
        //for (std::size_t i = 0 ; i < vect.size() ; ++i)
        //{
        //    if (vect.at(i) == value)
        //        return i;
        //}
        //return -1;
        typename std::vector<T>::const_iterator it = std::find(vect.begin(), vect.end(), value);
        if (it != vect.end() || (it == vect.end() && value == vect.back()))
            return it - vect.begin();
        else
            return -1;
    }
};

#endif
