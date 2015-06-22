//
//  DateTime.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 22/06/2015.
//
//

#include "DateTime.h"

namespace Utilities
{
    // Get current date/time, format is YYYY-MM-DD.HH:mm:ss
    std::string currentDateTime(const std::string & format)
    {
        time_t     now = time(0);
        struct tm  tstruct;
        char       buf[80];
        tstruct = *localtime(&now);
        // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
        // for more information about date/time format
        strftime(buf, sizeof(buf), format.c_str(), &tstruct);
        
        return buf;
    }
}