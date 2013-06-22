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
#include <stdexcept>

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

template <typename T>
std::vector<T> Diff(const std::vector<T> & vect1, const std::vector<T> & vect2)
{
    if (vect1.size() == vect2.size())
    {
        std::vector<T> vectres(vect1.size());
        
        for (std::size_t i = 0 ; i < vect1.size() ; ++i)
        {
            vectres[i] = vect1[i] - vect2[i];
        }
        return vectres;
    }
    else
    {
        throw std::runtime_error("Diff : Cannot compute diff, vectors do not have same size");
    }
}

#endif
