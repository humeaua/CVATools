//
//  Vector.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 05/05/13.
//
//

#ifndef CVATools_Vector_h
#define CVATools_Vector_h

#include <vector>

template <typename T>
T norm_2(const std::vector<T> & vect)
{
    T sum = 0;
    for (std::size_t i = 0 ; i < vect.size() ; ++i)
    {
        sum += vect[i] * vect[i];
    }
    return sqrt(sum);
}

#endif
