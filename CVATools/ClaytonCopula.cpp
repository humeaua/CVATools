//
//  ClaytonCopula.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 04/08/13.
//
//

#include "ClaytonCopula.h"
#include <cmath>

namespace Maths
{
    ClaytonCopula::ClaytonCopula(double dAlpha) : Copula(CLAYTON), dAlpha_(dAlpha)
    {}
    
    ClaytonCopula::~ClaytonCopula()
    {}
    
    double ClaytonCopula::ClaytonFunction1D(const double dX) const
    {
        return (pow(dX, -dAlpha_) - 1.0) / dAlpha_;
    }
    
    double ClaytonCopula::CopulaFunction(const Utilities::MyVector<double> & dVariables) const
    {
        return pow(dAlpha_ * dVariables.Sum() + 1.0, -1.0 / dAlpha_);
    }
}