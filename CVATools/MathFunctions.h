//
//  MathFunctions.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 22/06/13.
//
//

#ifndef __CVATools__MathFunctions__
#define __CVATools__MathFunctions__

#include <iostream>

namespace Maths
{
    double AccCumNorm(double x);
    
    struct DebyeFunction
    {
        double m_epsilon, m_nbStepInt, m_error;
        DebyeFunction();
        double operator()(double x, double k) const;
    };
}

#endif /* defined(__CVATools__MathFunctions__) */
