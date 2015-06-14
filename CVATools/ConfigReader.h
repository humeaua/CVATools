//
//  ConfigReader.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 24/05/2015.
//
//

#ifndef __CVATools__ConfigReader__
#define __CVATools__ConfigReader__

#include <stdio.h>
#include "CSVReader.h"
#include "Variant.h"
#include <map>
#include "Exception.h"

class ConfigReader
{
    CSVReader base;
    std::map<std::string, Utilities::Variant> m_internalMap;
    char m_delim;
    
    void Read();
public:
    ConfigReader(const std::string & filename, const char delim = '.');
    
    template<class T>
    void Fill(T & obj, const std::string & name) const
    {
        throw EXCEPTION("Not implemented, need to implement for special class");
    }
};

#endif /* defined(__CVATools__ConfigReader__) */
