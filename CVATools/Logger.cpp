//
//  Logger.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 23/06/2015.
//
//

#include "Logger.h"
#include "DateTime.h"
#include <fstream>

namespace Utilities
{
    Logger::Logger(std::ostream & os) : m_os(os)
    {}
    
    Logger::~Logger()
    {
        std::fstream * file = dynamic_cast<std::fstream*>(&m_os);
        if (file && file->is_open())
        {
            file->close();
        }
    }
    
    std::string Logger::getCurrentTime() const
    {
        // take default argument for now
        return currentDateTime();
    }
    
    void Logger::AddOneLine()
    {
        m_os << getCurrentTime() << " > " << std::endl;
    }
}