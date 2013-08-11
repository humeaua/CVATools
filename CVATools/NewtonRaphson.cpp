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

namespace Maths
{
    NewtonRaphson1D::NewtonRaphson1D(std::size_t iNIterMax, double dTolerance, double dEpsValueDeriv) : iNIterMax_(iNIterMax), dTolerance_(dTolerance), dEpsValueDeriv_(dEpsValueDeriv)
    {
        Utilities::requireException(dEpsValueDeriv > 0, "Epsilon value for derivative should be positive", "NewtonRaphson1D::NewtonRaphson1D");
        Utilities::requireException(dTolerance > 0, "Tolerance should be positive", "NewtonRaphson1D::NewtonRaphson1D");
    }
    
    double NewtonRaphson1D::algo_root_finder(double dInitialGuess) const
    {
        //  Newton Raphson method to find the yield that correspond to the price of the bond
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
                throw Utilities::MyException("NewtonRaphson1D::algo_root_finder : Derivative is too small.");
            }
            df0 = f(dx);
            
            //  Update number of iterations
            iNIter++;
        }
        
        if (iNIter >= iNIterMax_)
        {
            throw Utilities::MyException("NewtonRaphson1D::algo_root_finder : Newton Algorithm has not converged");
        }
        return dx;
    }
}