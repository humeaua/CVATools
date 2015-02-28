//
//  DoublePrecision.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 28/02/15.
//
//

#ifndef CVATools_DoublePrecision_h
#define CVATools_DoublePrecision_h

#include <cmath>
// Precision class to floor a T object up to N Digits

template<int N, class T>
T Precision(const T & t)
{
    double tenth = pow(10, N);
    T t_new = tenth * t;
    t_new = floor(t_new);
    
    return t_new / tenth;
}

#endif
