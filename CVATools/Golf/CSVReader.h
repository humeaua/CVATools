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

template <class T>
class CSVReader : public __gnu_cxx::iterator<std::input_iterator_tag, T>
{
    std::istream * m_input;
    char m_delim;
    std::string m_value;
public:
    
    CSVReader(const std::string & filename) : m_input(new std::fstream(filename.c_str())), m_delim(',')
    {
        ++ * this;
    }
    
    std::vector<T> operator *() const
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
    }
    
    std::istream & operator ++()
    {
        if (!getline(*m_input, m_value, '\r'))
        {
            m_input = 0;
        }
        return *m_input;
    }
};


#endif
