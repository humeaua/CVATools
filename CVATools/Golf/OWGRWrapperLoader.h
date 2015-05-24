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
#include "CSVReader.h"

template <class T>
class OWGRWrapperLoader
{
    OWGRVectorWrapper<T> obj;
    
public:
    
    const OWGRVectorWrapper<T> & get() const
    {
        return obj;
    }
    
    void Load(const std::string & filename)
    {
        CSVReader csvReader(filename);
        
        while (csvReader)
        {
            std::vector<T> value;
            csvReader >> value;
            obj.push_back(value[0]);
            
            ++csvReader;
        }
    }
};

#endif /* defined(__CVATools__OWGRWrapperLoader__) */
