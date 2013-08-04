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
    ClaytonCopula::ClaytonCopula(double dAlpha) : ArchimedeanCopula(CLAYTON), dAlpha_(dAlpha)
    {}
    
    ClaytonCopula::~ClaytonCopula()
    {}
    
    double ClaytonCopula::Generator(double dX) const
    {
        return (pow(dX, -dAlpha_) - 1.0) / dAlpha_;
    }
    
    double ClaytonCopula::GeneratorInverse(double x) const
    {
        return pow(1 + dAlpha_ * x, -1.0 / dAlpha_);
    }
    
    double ClaytonCopula::KendallTau() const
    {
        return dAlpha_ / (dAlpha_ + 2);
    }
}