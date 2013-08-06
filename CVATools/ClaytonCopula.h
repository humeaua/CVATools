//
//  ClaytonCopula.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 04/08/13.
//
//

#ifndef __CVATools__ClaytonCopula__
#define __CVATools__ClaytonCopula__

#include <iostream>
#include "ArchimedeanCopula.h"

namespace Maths
{
    class ClaytonCopula : public ArchimedeanCopula
    {
    protected:
        double dAlpha_;
    public:
        ClaytonCopula(double dAlpha);
        virtual ~ClaytonCopula();
        
        virtual double Generator(double x) const;
        virtual double GeneratorInverse(double x) const;
        
        virtual double KendallTau() const;
        
        virtual double InverseGeneratorRandomVariables(double u1, double u2) const;
        virtual std::vector<std::pair<double, double> > GenerateCorrelatedVariables(long long lSeed, std::size_t iNRealisations) const;
    };
}

#endif /* defined(__CVATools__ClaytonCopula__) */
