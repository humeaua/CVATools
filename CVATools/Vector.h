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
#include <numeric>
#include <algorithm>

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
        MyVector (const std::vector<C> & x) : std::vector<C>(x) {};
        
        virtual MyVector<C,Alloc> operator+(MyVector<C,Alloc> &v)
        {
            Utilities::requireException((*this).size() == v.size(), "Vectors are not the same size", "MyVector<C,Alloc> operator+(MyVector<C,Alloc> &)");
            std::vector<C> result;
            result.reserve(v.size());
            
            std::transform(this->begin(), this->end(), v.begin(), std::back_inserter(result), std::plus<C>());
            return MyVector<C>(result);
        };

        virtual MyVector<C,Alloc> operator-(MyVector<C,Alloc> &v)
        {
            Utilities::requireException((*this).size() == v.size(), "Vectors are not the same size", "MyVector<C,Alloc> operator-(MyVector<C,Alloc> &)");
            std::vector<C> result;
            result.reserve(v.size());
            
            std::transform(this->begin(), this->end(), v.begin(), std::back_inserter(result), std::minus<C>());
            return MyVector<C>(result);
        };
        
        virtual MyVector<C,Alloc> operator*(MyVector<C,Alloc> &v)
        {
            Utilities::requireException((*this).size() == v.size(), "Vectors are not the same size", "MyVector<C,Alloc> operator* (MyVector<C,Alloc> &)");
            std::vector<C> result;
            result.reserve(v.size());
            
            std::transform(this->begin(), this->end(), v.begin(), std::back_inserter(result), std::multiplies<C>());
            return MyVector<C>(result);
        };
        
        virtual MyVector<C,Alloc> operator/(MyVector<C,Alloc> &v)
        {
            Utilities::requireException((*this).size() == v.size(), "Vectors are not the same size", "MyVector<C,Alloc> operator/(MyVector<C,Alloc> &)");
            std::vector<C> result;
            result.reserve(v.size());
            
            std::transform(this->begin(), this->end(), v.begin(), std::back_inserter(result), std::divides<C>());
            return MyVector<C>(result);
        };
        
        virtual MyVector<C,Alloc> operator+(C value)
        {
            std::transform(this->begin(), this->end(), this->begin(), bind2nd(std::plus<C>(), value));
            return *this;
        };
        
        virtual MyVector<C,Alloc> operator-(C value)
        {
            std::transform(this->begin(), this->end(), this->begin(), bind2nd(std::minus<C>(), value));
            return *this;
        };
        
        virtual MyVector<C,Alloc> operator*(C value)
        {
            std::transform(this->begin(), this->end(), this->begin(), bind2nd(std::multiplies<C>(), value));
            return *this;
        };
        
        virtual MyVector<C,Alloc> operator/(C value)
        {
            Utilities::requireException(value != 0.0, "value is 0", "MyVector<C,Alloc> operator/(C value)");
            std::transform(this->begin(), this->end(), this->begin(), bind2nd(std::divides<C>(), value));
            return *this;
        };
        
        virtual C Sum() const
        {
            return std::accumulate(this->begin(), this->end(), 0);
        };
    };
    
    template <typename T>
    T norm_2(const std::vector<T> & vect)
    {
        return sqrt(std::inner_product(vect.begin(), vect.end(), vect.begin(), 0.0));
    }
    
    template <typename T>
    std::vector<T> Diff(const std::vector<T> & vect1, const std::vector<T> & vect2)
    {
        Utilities::requireException(vect1.size() == vect2.size(), "Cannot compute diff, vectors do not have same size","Diff");
        std::vector<T> result;
        result.reserve(vect1.size());
        
        std::transform(vect1.begin(), vect1.end(), vect2.begin(), std::back_inserter(result), std::minus<T>());
        return result;
    }
}

#endif
