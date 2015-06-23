//
//  Logger.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 23/06/2015.
//
//

#ifndef __CVATools__Logger__
#define __CVATools__Logger__

#include <stdio.h>
#include <iostream>

namespace Utilities
{
    class Logger
    {
    private:
        std::ostream & m_os;
        
        std::string getCurrentTime() const;
    public:
        Logger(std::ostream & os);
        
        template <class T>
        Logger& operator<<(const T& obj)
        {
            m_os << getCurrentTime() << " > " <<obj << std::endl;
            return *this;
        }
        
        void AddOneLine();
    };
}

#endif /* defined(__CVATools__Logger__) */
