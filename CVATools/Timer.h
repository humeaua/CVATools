//
//  Timer.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 27/06/2015.
//
//

#ifndef __CVATools__Timer__
#define __CVATools__Timer__

#include <stdio.h>
#include <iostream>

namespace Utilities
{
    class Timer
    {
        clock_t m_start;
    public:
        Timer();
        
        virtual std::string TimeElapsed() const;
    };
}

#endif /* defined(__CVATools__Timer__) */
