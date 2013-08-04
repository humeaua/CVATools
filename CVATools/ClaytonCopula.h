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
#include "Copula.h"

namespace Maths
{
    class ClaytonCopula : public Copula
    {
    protected:
        double dAlpha_;
    public:
        ClaytonCopula(double dAlpha);
        virtual ~ClaytonCopula();
        
        virtual double ClaytonFunction1D(const double dX) const;
        virtual double CopulaFunction(const Utilities::MyVector<double> & dVariables) const;
    };
}

#endif /* defined(__CVATools__ClaytonCopula__) */
