//
//  Vector.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 02/07/13.
//
//

#include "Vector.h"
#include "Require.h"

template<class C>
std::vector<C> MyVector<C>::operator*(std::vector<C> & v)
{
    Utilities::requireException((*this).size() == v.size(), "Vectors are not the same size for *");
    std::vector<C> result(v.size());
    for (std::size_t i = 0 ; i < v.size() ; ++i)
    {
        result[i] = (*this)[i] * v[i];
    }
    return result;
}

template<class C>
std::vector<C> MyVector<C>::operator-(std::vector<C> & v)
{
    Utilities::requireException((*this).size() == v.size(), "Vectors are not the same size for -");
    std::vector<C> result(v.size());
    for (std::size_t i = 0 ; i < v.size() ; ++i)
    {
        result[i] = (*this)[i] - v[i];
    }
    return result;
}

template<class C>
std::vector<C> MyVector<C>::operator+(std::vector<C> & v)
{
    Utilities::requireException((*this).size() == v.size(), "Vectors are not the same size for +");
    std::vector<C> result(v.size());
    for (std::size_t i = 0 ; i < v.size() ; ++i)
    {
        result[i] = (*this)[i] + v[i];
    }
    return result;
}

template<class C>
std::vector<C> MyVector<C>::operator/(std::vector<C> & v)
{
    Utilities::requireException((*this).size() == v.size(), "Vectors are not the same size for /");
    std::vector<C> result(v.size());
    for (std::size_t i = 0 ; i < v.size() ; ++i)
    {
        Utilities::requireException(v[i] != 0.0, "value is 0");
        result[i] = (*this)[i] / v[i];
    }
    return result;
}
