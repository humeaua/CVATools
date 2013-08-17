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
        Utilities::requireException(dTheta_ < EPSILON_FRANK_COPULA, "Frank copula parameter is too small", "FrankCopula::FrankCopula");
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
        return 1.0 + 4.0 * (Maths::DebyeFunction(-dTheta_, 1.0) - 1.0) / dTheta_;
    }
}