//
//  Exception.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 13/07/13.
//
//

#ifndef __CVATools__Exception__
#define __CVATools__Exception__

#include <iostream>
#include <stdexcept>
#include <stdlib.h>

namespace Utilities
{
    class MyException : public std::runtime_error
    {
    public:
        explicit MyException(const std::string & cMessage);
    };
   
#define S(x) #x
#define S_(x) S(x)
#define S__LINE__ S_(__LINE__)
    
    /* use S__LINE__ instead of __LINE__ */
#ifndef EXCEPTION
#define EXCEPTION(x) Utilities::MyException(std::string(x) + " in function : " + __FUNCTION__ + " (line " + S__LINE__ + ")")
#endif
}

#endif /* defined(__CVATools__Exception__) */
