//
//  StochCorrel.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 24/08/13.
//
//

#include "StochCorrel.h"
#include "Require.h"
#include <cmath>

namespace Finance
{
    namespace Processes
    {
        StochCorrel::StochCorrel(double dLambda, double dRhoInfty, double dSigma, double dRho0, long long &lSeed) : dSigma_(dSigma), dLambda_(dLambda), dRhoInfty_(dRhoInfty), DiffusionProcess(dRho0, true, true, true, true, 1.0, -1.0, lSeed)
        {
            REQUIREEXCEPTION(dX0_ >= -1.0 && dX0_ <= 1.0, "Stochastic Correlation initial value has to be between -1 and 1");
            REQUIREEXCEPTION(dRhoInfty_ >= -1.0 && dRhoInfty_ <= 1.0, "Stochastic Correlation initial value has to be between -1 and 1");
        }
        
        double StochCorrel::drift(double dt, double dx) const
        {
            return dLambda_ * (dRhoInfty_ - dx);
        }
        
        double StochCorrel::diffusion(double dt, double dx) const
        {
            return dSigma_ * sqrt(1.0 - dx * dx);
        }
        
        double StochCorrel::expectation(double t0, double x0, double dt) const
        {
            return x0 * exp(-dLambda_ * dt) + dRhoInfty_ * (1.0 - exp(-dLambda_ * dt));
        }
        
        double StochCorrel::variance(double t0, double x0, double dt) const
        {
            return dSigma_ * dSigma_ * (1 - x0 * x0) * dt;
        }
    }
}