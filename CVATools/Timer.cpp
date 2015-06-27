//
//  Timer.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 27/06/2015.
//
//

#include "Timer.h"
#include <sstream>
#include <iomanip>

namespace Utilities
{
    Timer::Timer()
    {
        m_start = clock();
    }
    
    std::string Timer::TimeElapsed() const
    {
        clock_t time = clock();
        
        std::stringstream ss;
        ss << std::setprecision(5);
        ss << "Time Elapsed : " << (double)(time-m_start) / CLOCKS_PER_SEC << " seconds";
        
        return ss.str();
    }
}