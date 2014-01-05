//
//  GumbelCopula.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 10/08/13.
//
//

#include "GumbelCopula.h"
#include <cmath>

namespace Maths
{
    GumbelCopula::GumbelCopula(double dTheta) : dTheta_(dTheta), ArchimedeanCopula(GUMBEL)
    {
        REQUIREEXCEPTION(dTheta > 1.0, "Theta has to be higher than 1");
    }
    
    double GumbelCopula::Generator(double x) const
    {
       REQUIREEXCEPTION(x > 0.0 && x < 1.0, "x has to be between 0.0 and 1.0");
        return pow(-log(x), dTheta_);
    }
    
    double GumbelCopula::GeneratorInverse(double x) const
    {
        return exp(-pow(x, 1.0 / dTheta_));
    }
    
    double GumbelCopula::KendallTau() const
    {
        return 1.0 - 1.0 / dTheta_;
    }
}