//
//  Logger.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 23/06/2015.
//
//

#include "Logger.h"
#include "DateTime.h"

namespace Utilities
{
    Logger::Logger(std::ostream & os) : m_os(os)
    {}
    
    std::string Logger::getCurrentTime() const
    {
        // take default argument for now
        return currentDateTime();
    }
    
    void Logger::AddOneLine()
    {
        m_os << std::endl;
    }
}