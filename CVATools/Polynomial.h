//
//  Polynomial.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 10/02/14.
//
//

#ifndef __CVATools__Polynomial__
#define __CVATools__Polynomial__

#include <iostream>

namespace Maths
{
    class Polynomial
    {
    protected:
        size_t m_Degree;
    public:
        Polynomial();
        Polynomial(const std::size_t & iDegree);
        virtual ~Polynomial();
        
        virtual double operator()(double x, size_t i) const = 0;
        virtual double deriv(double x, size_t i) const = 0;
    };
}

#endif /* defined(__CVATools__Polynomial__) */
