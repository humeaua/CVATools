//
//  CSVReader.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 29/03/15.
//
//

#ifndef CVATools_CSVReader_h
#define CVATools_CSVReader_h

#include <fstream>
#include <iostream>
#include "StringUtilities.h"
#include <sstream>
#include "Exception.h"

class CSVReader
{
    // need raw pointer since it has to be null
    std::istream * m_input;
    char m_delim;
    std::string m_value;
public:
    
    CSVReader(const std::string & filename,
              const char delim = ',') : m_input(new std::fstream(filename.c_str())), m_delim(delim)
    {
        ++ * this;
    }
    
    ~CSVReader()
    {
        delete m_input;
        m_input = NULL;
    }
    
    /*template<class T>
    std::vector<T> operator >>(const CSVReader &) const
    {
        std::istringstream ss(m_value);
        std::vector<std::string> stringValues = Utilities::Split(m_value, m_delim);
        std::vector<T> vectType(stringValues.size());
        for (size_t i = 0 ; i < stringValues.size() ; ++i)
        {
            std::stringstream ss ;
            ss << stringValues[i];
            ss >> vectType[i];
        }
        return vectType;
    }*/
    
    void operator ++()
    {
        if (!getline(*m_input, m_value))
        {
            m_input = 0;
        }
        //return *m_input; // this is pretty bad since we dereference the NULL pointer
    }
    
    operator bool() const
    {
        return m_input != NULL;
    }
    
    const std::string & getValue() const
    {
        return m_value;
    }
    
    const char & getDelim() const
    {
        return m_delim;
    }
};

template <class T>
CSVReader & operator >> (CSVReader & reader, std::vector<T> & vectType)
{
    std::vector<std::string> stringValues = Utilities::Split(reader.getValue(), reader.getDelim());
    vectType.resize(stringValues.size());
    for (size_t i = 0 ; i < stringValues.size() ; ++i)
    {
        std::stringstream ss ;
        ss << stringValues[i];
        ss >> vectType[i];
    }
    return reader;
}

template <class T>
CSVReader & operator >> (CSVReader & reader, T & value)
{
    std::vector<std::string> stringValues = Utilities::Split(reader.getValue(), reader.getDelim());
    if (stringValues.size() != 1)
    {
        throw EXCEPTION("Vector is of size stricly above one, you must use the vector version of the operator >>");
    }
    std::stringstream ss ;
    ss << stringValues[0];
    ss >> value;
    return reader;
}

#endif
