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
#include "DateTime.h"

namespace Utilities
{
    class Logger
    {
    private:
        std::ostream & m_os;
        
        std::string getCurrentTime() const;
    public:
        Logger(std::ostream & os);
        ~Logger();
        
        void AddOneLine();
        template<class T>
        void PutLine(const T & t)
        {
            m_os << currentDateTime() << " > " << t << std::endl;
            AddOneLine();
        }
    };
}

#endif /* defined(__CVATools__Logger__) */
