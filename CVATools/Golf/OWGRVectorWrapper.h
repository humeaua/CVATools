//
//  OWGRVectorWrapper.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 28/01/15.
//
//

#ifndef CVATools_OWGRVectorWrapper_h
#define CVATools_OWGRVectorWrapper_h

#include <iostream>
#include <vector>
#include "Exception.h"

template <class T>
class OWGRVectorWrapper
{
    std::vector<T> m_vect;
public:
    OWGRVectorWrapper(size_t size = 0, const T& t = T(0))
    {
        resize(size, t);
    }
    
    void resize(size_t size, const T& t = T(0))
    {
        m_vect.resize(size,t);
    }
    
    void push_back(const T& t)
    {
        m_vect.push_back(t);
    }
    
    size_t size() const
    {
        return m_vect.size();
    }
    
    const T & operator[](const size_t & i) const
    {
        if (i < size())
        {
            return m_vect[i];
        }
        else
        {
            return m_vect.back();
        }
    };
    
    std::vector<T> & vector()
    {
        return m_vect;
    }
};

#endif
