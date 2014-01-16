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

namespace Utilities
{
    class MyException : public std::runtime_error
    {
    public:
        explicit MyException(const std::string & cMessage);
    };
    
#ifndef EXCEPTION
#define EXCEPTION(x) Utilities::MyException(x + "function : " + __FUNCTION__ + "(line " + __LINE__ + ")")
#endif
}

#endif /* defined(__CVATools__Exception__) */
