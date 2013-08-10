//
//  FrankCopula.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 10/08/13.
//
//

#ifndef __CVATools__FrankCopula__
#define __CVATools__FrankCopula__

#include <iostream>
#include "ArchimedeanCopula.h"

namespace Maths
{
#ifndef EPSILON_FRANK_COPULA
#define EPSILON_FRANK_COPULA 1e-03
#endif
    
    class FrankCopula : public ArchimedeanCopula
    {
        double dTheta_;
        
        double IntExp(double x) const;
    public:
        FrankCopula(double dTheta);
        
        virtual double Generator(double x) const;
        virtual double GeneratorInverse(double x) const;
        
        virtual double KendallTau() const;
    };
}

#endif /* defined(__CVATools__FrankCopula__) */
