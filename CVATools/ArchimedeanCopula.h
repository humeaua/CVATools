//
//  ArchimedeanCopula.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 04/08/13.
//
//

#ifndef __CVATools__ArchimedeanCopula__
#define __CVATools__ArchimedeanCopula__

#include <iostream>
#include "Copula.h"

namespace Maths
{
    class ArchimedeanCopula : public Copula
    {
    public:
        ArchimedeanCopula();
        ArchimedeanCopula(CopulaType eCopulaType);
        
        virtual double Generator(double x) const = 0;
        virtual double GeneratorInverse(double x) const = 0;
        
        virtual double CopulaFunction(const Utilities::MyVector<double> & dVariables) const;
    };
}

#endif /* defined(__CVATools__ArchimedeanCopula__) */
