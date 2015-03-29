//
//  OWGRWrapperLoader.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 27/03/15.
//
//

#ifndef __CVATools__OWGRWrapperLoader__
#define __CVATools__OWGRWrapperLoader__

#include <iostream>
#include "OWGRVectorWrapper.h"

template <class T>
class OWGRWrapperLoader
{
    OWGRVectorWrapper<T> obj;
    
public:
    
    const OWGRVectorWrapper<T> & get() const
    {
        return obj;
    }
    
    void Load(const std::ifstream & stream)
    {}
};

#endif /* defined(__CVATools__OWGRWrapperLoader__) */
