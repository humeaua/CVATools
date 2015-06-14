//
//  Variant.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 08/09/13.
//
//

#ifndef __CVATools__Variant__
#define __CVATools__Variant__

#include <iostream>
#include "Exception.h"

namespace Utilities
{
    class Variant
    {
    protected:
        double m_d;
        int m_i;
        long m_l;
        std::string m_c;
        
        enum TYPE
        {
            DOUBLE, INT, LONG, STRING, MULTI, ERROR
        };
        
        TYPE m_type;
        
        void SetType(TYPE newType);
    public:
        //  need default constructor since used in map
        Variant();
        Variant(double d);
        Variant(int i);
        Variant(long l);
        Variant(const std::string & m_c);
        
        // Setters
        void SetDouble(double d0);
        void SetInt(int i0);
        void SetLong(long l0);
        void SetString(const std::string & c0);
        
        // Getters
        double GetDouble() const;
        int GetInt() const;
        long GetLong() const;
        const std::string & GetString() const;
    };
}

#endif /* defined(__CVATools__Variant__) */
