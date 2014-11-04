//
//  NewtonRaphson.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 03/06/13.
//
//

#include "NewtonRaphson.h"
#include <cmath>
#include "Require.h"
#include "Exception.h"

namespace Maths
{
    NewtonRaphson1D::NewtonRaphson1D() : iNIterMax_(100), dTolerance_(1.0e-6), dEpsValueDeriv_(1.0e-6)
    {}
    
    NewtonRaphson1D::NewtonRaphson1D(std::size_t iNIterMax, double dTolerance, double dEpsValueDeriv) : iNIterMax_(iNIterMax), dTolerance_(dTolerance), dEpsValueDeriv_(dEpsValueDeriv)
    {
        REQUIREEXCEPTION(dEpsValueDeriv > 0, "Epsilon value for derivative should be positive");
        REQUIREEXCEPTION(dTolerance > 0, "Tolerance should be positive");
    }
    
    double NewtonRaphson1D::algo_root_finder(double dInitialGuess) const
    {
        //  Newton Raphson method to find the zero of a function : the function must not have a double root 
        double dx = dInitialGuess, dfdx;
        std::size_t iNIter = 0;
        
        double df0 = f(dx);
        
        while (fabs(df0) > dTolerance_ && iNIter <= iNIterMax_)
        {
            dfdx = df(dx);
            if (fabs(dfdx) > dEpsValueDeriv_)
            {
                dx -= df0 / df(dx);
            }
            else
            {
                throw EXCEPTION("Derivative is too small.");
            }
            df0 = f(dx);
            
            //  Update number of iterations
            ++iNIter;
        }
        
        if (iNIter >= iNIterMax_)
        {
            throw EXCEPTION("Newton Algorithm has not converged");
        }
        return dx;
    }
}