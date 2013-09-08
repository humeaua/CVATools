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

namespace Utilities
{
    class Variant
    {
    protected:
        double d;
        int i;
        long l;
        std::string c;
    public:
        Variant();
        
        // Setters
        virtual void SetDouble(double d0);
        virtual void SetInt(int i0);
        virtual void SetLong(long l0);
        virtual void SetString(const std::string & c0);
        
        // Getters
        virtual double GetDouble() const;
        virtual int GetInt() const;
        virtual long GetLong() const;
        virtual std::string GetString() const;
    };
}

#endif /* defined(__CVATools__Variant__) */
