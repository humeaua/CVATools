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
#include "Require.h"

namespace Utilities
{
    template <class C, class Alloc = std::allocator<C> >
    class MyVector : public std::vector<C, Alloc>
    {
    public:
        MyVector() : std::vector<C>() {};
        explicit  MyVector (const std::allocator<C>& alloc = std::allocator<C>()) : std::vector<C>(alloc) {};
        
        explicit MyVector (std::size_t n, const C & val = C(),
                           const std::allocator<C>& alloc = std::allocator<C>()) : std::vector<C>(n, val, alloc) {};
        
        template <class InputIterator>
        MyVector (InputIterator first, InputIterator last,
                  const std::allocator<C>& alloc = std::allocator<C>()) : std::vector<C>(first, last, alloc) {};
        
        MyVector (const MyVector & x) : std::vector<C>(x) {};
        
        virtual MyVector<C,Alloc> operator+(MyVector<C,Alloc> &v)
        {
            Utilities::requireException((*this).size() == v.size(), "Vectors are not the same size", "MyVector<C,Alloc> operator+(MyVector<C,Alloc> &)");
            MyVector<C,Alloc> result(v.size());
            for (std::size_t i = 0 ; i < v.size() ; ++i)
            {
                result[i] = (*this)[i] + v[i];
            }
            return result;
        };
        
        virtual MyVector<C,Alloc> operator-(MyVector<C,Alloc> &v)
        {
            Utilities::requireException((*this).size() == v.size(), "Vectors are not the same size", "MyVector<C,Alloc> operator-(MyVector<C,Alloc> &)");
            MyVector<C,Alloc> result(v.size());
            for (std::size_t i = 0 ; i < v.size() ; ++i)
            {
                result[i] = (*this)[i] - v[i];
            }
            return result;
        };
        
        virtual MyVector<C,Alloc> operator*(MyVector<C,Alloc> &v)
        {
            Utilities::requireException((*this).size() == v.size(), "Vectors are not the same size for *", "MyVector<C,Alloc> operator*(MyVector<C,Alloc> &)");
            MyVector<C,Alloc> result(v.size());
            for (std::size_t i = 0 ; i < v.size() ; ++i)
            {
                result[i] = (*this)[i] * v[i];
            }
            return result;
        };
        
        virtual MyVector<C,Alloc> operator/(MyVector<C,Alloc> &v)
        {
            Utilities::requireException((*this).size() == v.size(), "Vectors are not the same size for /", "MyVector<C,Alloc> operator/(MyVector<C,Alloc> &)");
            MyVector<C,Alloc> result(v.size());
            for (std::size_t i = 0 ; i < v.size() ; ++i)
            {
                Utilities::requireException(v[i] != 0.0, "value is 0");
                result[i] = (*this)[i] / v[i];
            }
            return result;
        };
        
        virtual MyVector<C,Alloc> operator+(C value)
        {
            MyVector<C,Alloc> result(this->size());
            for (std::size_t i = 0 ; i < this->size() ; ++i)
            {
                result[i] = (*this)[i] + value;
            }
            return result;
        };
        
        virtual MyVector<C,Alloc> operator-(C value)
        {
            MyVector<C,Alloc> result(this->size());
            for (std::size_t i = 0 ; i < this->size() ; ++i)
            {
                result[i] = (*this)[i] - value;
            }
            return result;
        };
        
        virtual MyVector<C,Alloc> operator*(C value)
        {
            MyVector<C,Alloc> result(this->size());
            for (std::size_t i = 0 ; i < this->size() ; ++i)
            {
                result[i] = (*this)[i] * value;
            }
            return result;
        };
        
        virtual MyVector<C,Alloc> operator/(C value)
        {
            Utilities::requireException(value != 0.0, "value is 0", "MyVector<C,Alloc> operator/(C value)");
            MyVector<C,Alloc> result(this->size());
            for (std::size_t i = 0 ; i < this->size() ; ++i)
            {
                result[i] = (*this)[i] / value;
            }
            return result;
        };
        
        virtual C Sum() const
        {
            C res = (*this)[0];
            for (std::size_t i = 1 ; i < this->size() ; ++i)
            {
                res += (*this)[i];
            }
            return res;
        };
    };
    
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
        Utilities::requireException(vect1.size() == vect2.size(), "Cannot compute diff, vectors do not have same size","Diff");
        
        std::vector<T> vectres(vect1.size());
        
        for (std::size_t i = 0 ; i < vect1.size() ; ++i)
        {
            vectres[i] = vect1[i] - vect2[i];
        }
        return vectres;
    }
}

#endif
