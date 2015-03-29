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

template <class T>
class CSVReader : public __gnu_cxx::iterator<std::input_iterator_tag, T>
{
    std::istream * m_input;
    char m_delim;
    std::string m_value;
public:
    
    csv_istream_iterator(char delim = ',') : m_input(0), m_delim(delim)
    {
    }
    
    csv_istream_iterator(std::istream & in, char delim = ',') : m_input(&in), m_delim(delim)
    {
        ++ * this;
    }
    
    const T operator *() const
    {
        std::istringstream ss(m_value);
        T value;
        ss >> value;
        return value;
    }
    
    std::istream & operator ++()
    {
        if (!getline(*m_input, m_value, m_delim))
        {
            m_input = 0;
        }
        return *m_input;
    }
    
    bool operator !=(const csv_istream_iterator & rhs) const
    {
        return m_input != rhs.m_input;
    }
    };

#endif
