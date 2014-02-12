//
//  HermitePolynomials.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 10/02/14.
//
//

#ifndef __CVATools__HermitePolynomials__
#define __CVATools__HermitePolynomials__

#include <iostream>
#include <vector>
#include "Polynomial.h"
#include <memory>

namespace Maths
{
    class HermitePolynomial3 : public Polynomial
    {
    private:
        
    public:
        HermitePolynomial3();
        virtual ~HermitePolynomial3();
        
        virtual double operator()(double x, size_t i) const;
        virtual double deriv(double x, size_t i) const;
        virtual double deriv2(double x, size_t i) const;
    };
    
    class HermitePolynomial5 : public Polynomial
    {
    public:
        HermitePolynomial5();
        virtual ~HermitePolynomial5();
        
        virtual double operator()(double x, size_t i) const;
        virtual double deriv(double x, size_t i) const;
        virtual double deriv2(double x, size_t i) const;
    };
    
    class HermitePolynomials
    {
    protected:
        std::vector<std::auto_ptr<Polynomial> > m_polynomials;
        
    public:
        
    };
}

#endif /* defined(__CVATools__HermitePolynomials__) */
