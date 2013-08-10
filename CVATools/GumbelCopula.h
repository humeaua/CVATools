//
//  GumbelCopula.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 10/08/13.
//
//

#ifndef __CVATools__GumbelCopula__
#define __CVATools__GumbelCopula__

#include <iostream>
#include "ArchimedeanCopula.h"

namespace Maths
{
    class GumbelCopula : public ArchimedeanCopula
    {
        double dTheta_;
        
    public:
        GumbelCopula(double dTheta);
        
        virtual double Generator(double x) const;
        virtual double GeneratorInverse(double x) const;
        
        virtual double KendallTau() const;
    };
    
}

#endif /* defined(__CVATools__GumbelCopula__) */
