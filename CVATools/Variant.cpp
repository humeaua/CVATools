//
//  Variant.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 08/09/13.
//
//

#include "Variant.h"
#include <cmath>

namespace Utilities
{
    //  need default constructor since used in map
    Variant::Variant() : m_type(ERROR), m_i(0), m_l(0L), m_d(0.0)
    {}
    
    Variant::Variant(int i) : m_d(0.0), m_i(i), m_l(0L), m_type(INT)
    {}
    
    Variant::Variant(double d) : m_d(d), m_l(0L), m_i(0), m_type(DOUBLE)
    {}
    
    Variant::Variant(long l) : m_d(0), m_l(l), m_i(0), m_type(LONG)
    {}
    
    Variant::Variant(const std::string & s) : m_c(s), m_d(0.0), m_i(0), m_l(0L), m_type(STRING)
    {
        // conversion of string to number
        std::stringstream ss;
        ss << m_c;
        ss >> m_d;
        m_i = static_cast<int>(m_d);
        m_l = static_cast<long>(m_d);
        SetType(Variant::MULTI);
    }
    
    void Variant::SetType(Utilities::Variant::TYPE newType)
    {
        if (m_type == newType)
        {
            //  do not do anything since we have the same type
        }
        else
        {
            //  change type to multi
            m_type = Utilities::Variant::MULTI;
        }
    }
    
    void Variant::SetDouble(double d0)
    {
        m_d = d0;
        SetType(DOUBLE);
    }
    
    void Variant::SetInt(int i0)
    {
        m_i = i0;
        SetType(INT);
    }
    void Variant::SetLong(long l0)
    {
        m_l = l0;
        SetType(LONG);
    }
    
    void Variant::SetString(const std::string & c0)
    {
        m_c = c0;
        SetType(STRING);
    }
    
    double Variant::GetDouble() const
    {
        return m_d;
    }
    
    int Variant::GetInt() const
    {
        return m_i;
    }
    
    long Variant::GetLong() const
    {
        return m_l;
    }
    
    const std::string & Variant::GetString() const
    {
        return m_c;
    }
}