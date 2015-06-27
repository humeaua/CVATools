//
//  DateTime.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 22/06/2015.
//
//

#ifndef __CVATools__DateTime__
#define __CVATools__DateTime__

#include <stdio.h>
#include <iostream>

namespace Utilities
{
    std::string currentDateTime(const std::string & format = "%Y-%m-%d.%H-%M-%S");
}

#endif /* defined(__CVATools__DateTime__) */
