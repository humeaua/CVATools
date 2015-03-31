//
//  ConfigLoader.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 27/03/15.
//
//

#ifndef CVATools_ConfigLoader_h
#define CVATools_ConfigLoader_h

#include <iostream>
#include <fstream>

template<class T>
class ConfigLoader
{
    T obj;
public:
    ConfigLoader(const std::string & filename)
    {
        obj.Load(filename);
    }
    
    const T & get() const
    {
        return obj;
    }
};

#endif
