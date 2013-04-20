//
//  MyArray.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 20/04/13.
//
//

#ifndef CVATools_MyArray_h
#define CVATools_MyArray_h

#include <valarray>

template <class T>
std::valarray<T> vectortovalarray(const std::vector<T>& vect)
{
    std::size_t n = vect.size();
    T * pT = new T[n];
    for (std::size_t i = 0 ; i < n ; ++i)
    {
        pT[i] = vect[i];
    }
    std::valarray<T> result(pT, n);
    delete pT;
    return result;
}

template <class T>
class MyArray : public std::valarray<T>
{
public:
    MyArray(const std::vector<T>& vect) : std::valarray<T>(vectortovalarray(vect))
    {}
};

#endif
