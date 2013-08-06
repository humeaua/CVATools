//
//  ClaytonCopula.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 04/08/13.
//
//

#include "ClaytonCopula.h"
#include <cmath>
#include <tr1/random>

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
    
    double ClaytonCopula::InverseGeneratorRandomVariables(double u1, double u2) const
    {
        return pow(1.0 - pow(u1, -dAlpha_) + pow(
                                                 +u2 / dAlpha_ * pow(u1, dAlpha_ + 1), -dAlpha_), -1.0 / dAlpha_);
    }
    
    std::vector<std::pair<double, double> > ClaytonCopula::GenerateCorrelatedVariables(long long lSeed, std::size_t iNRealisations) const
    {
        std::tr1::ranlux64_base_01 eng; // core engine class
        eng.seed(lSeed);
        std::tr1::uniform_real<double> dist(0.0,1.0);
        double u1, u2;
        
        std::vector<std::pair<double, double> > dResults;
        for (std::size_t i = 0 ; i < iNRealisations ; ++i)
        {
            u1 = dist(eng);
            u2 = dist(eng);
            dResults.push_back(std::make_pair(u1, InverseGeneratorRandomVariables(u1, u2)));
        }
        return dResults;
    }
}