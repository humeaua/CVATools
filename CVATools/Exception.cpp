//
//  Exception.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 13/07/13.
//
//

#include "Exception.h"

namespace Utilities
{
    MyException::MyException(const std::string & cMessage) : std::runtime_error(cMessage)
    {}
    
    const char * MyException::what() const throw()
    {
        return std::runtime_error::what();
    }
}