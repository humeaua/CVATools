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
    class HermitePolynomial : public Polynomial
    {
    private:
        
    public:
        HermitePolynomial();
        virtual ~HermitePolynomial();
        
        virtual double operator()(double x, size_t i) const;
        virtual double deriv(double x, size_t i) const;
    };
    
    class HermitePolynomials
    {
    protected:
        std::vector<std::auto_ptr<Polynomial> > m_polynomials;
        
    public:
        
    };
}

#endif /* defined(__CVATools__HermitePolynomials__) */
