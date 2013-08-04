//
//  NewtonRaphson.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 03/06/13.
//
//

#ifndef __CVATools__NewtonRaphson__
#define __CVATools__NewtonRaphson__

#include <iostream>

namespace Maths
{
    class NewtonRaphson1D
    {
    protected:
        std::size_t iNIterMax_;
        double dTolerance_;
        double dEpsValueDeriv_;
        
    public:
        NewtonRaphson1D(std::size_t iNIterMax = 100, double dTolerance = 1e-06, double dEpsValueDeriv = 1e-06);
        
        virtual double f(double x) const = 0;
        virtual double df(double x) const = 0;
        
        virtual double algo_root_finder(double dInitialGuess) const;
    };
}

#endif /* defined(__CVATools__NewtonRaphson__) */
