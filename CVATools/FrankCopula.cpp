//
//  FrankCopula.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 10/08/13.
//
//

#include "FrankCopula.h"
#include <cmath>
#include "MathFunctions.h"

namespace Maths
{
    FrankCopula::FrankCopula(double dTheta) : dTheta_(dTheta), ArchimedeanCopula(FRANK)
    {
        REQUIREEXCEPTION(dTheta_ < EPSILON_FRANK_COPULA, "Frank copula parameter is too small");
    }
    
    double FrankCopula::IntExp(double x) const
    {
        return exp(-dTheta_ * x) - 1.0;
    }
    
    double FrankCopula::Generator(double x) const
    {
        return -log(IntExp(x) / IntExp(1.0));
    }
    
    double FrankCopula::GeneratorInverse(double x) const
    {
        return -1.0 / dTheta_ * log(1.0 + exp(-x) * IntExp(1.0));
    }
    
    double FrankCopula::KendallTau() const
    {
        Maths::DebyeFunction debyeFunction;
        return 1.0 + 4.0 * (debyeFunction(-dTheta_, 1.0) - 1.0) / dTheta_;
    }
}