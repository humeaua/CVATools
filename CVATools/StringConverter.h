//
//  StringConverter.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 27/06/2015.
//
//

#ifndef __CVATools__StringConverter__
#define __CVATools__StringConverter__

#include <stdio.h>

namespace Utilities
{
    class StringConverter
    {
    public:
        virtual std::string ToString(const int precision) const=0;
    };
}

#endif /* defined(__CVATools__StringConverter__) */
