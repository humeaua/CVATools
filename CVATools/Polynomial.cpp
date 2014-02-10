//
//  Polynomial.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 10/02/14.
//
//

#include "Polynomial.h"

namespace Maths
{
    Polynomial::Polynomial() : m_Degree(0)
    {}
    
    Polynomial::Polynomial(const std::size_t & iDegree) : m_Degree(iDegree)
    {}
    
    Polynomial::~Polynomial()
    {}
}