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
    Variant::Variant() : d(0.0), i(0), l(0)
    {}
    
    void Variant::SetDouble(double d0)
    {
        d = d0;
    }
    
    void Variant::SetInt(int i0)
    {
        i = i0;
    }
    void Variant::SetLong(long l0)
    {
        l = l0;
    }
    
    void Variant::SetString(const std::string & c0)
    {
        c = c0;
    }
    
    double Variant::GetDouble() const
    {
        return d;
    }
    
    int Variant::GetInt() const
    {
        return i;
    }
    
    long Variant::GetLong() const
    {
        return l;
    }
    
    std::string Variant::GetString() const
    {
        return c;
    }
    
    bool Variant::operator==(const Variant & sRight)
    {
        return (std::abs(sRight.GetDouble() - d) < std::numeric_limits<double>::epsilon()
                && sRight.GetInt() == i
                && sRight.GetLong() == l
                && sRight.GetString() == c);
    }
}