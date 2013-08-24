//
//  StochCorrel.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 24/08/13.
//
//

#ifndef __CVATools__StochCorrel__
#define __CVATools__StochCorrel__

#include <iostream>
#include "DiffusionProcess.h"

namespace Finance
{
    namespace Processes
    {
        
        // Implementation of a stochastic correlation processus
        // dx_t = lambda (x_infty - x_t) dt + sigma sqrt(1 - x_t^2) dW_t
        
        class StochCorrel : public DiffusionProcess
        {
        protected:
            // Mean reversion
            double dLambda_;
            // final Level
            double dRhoInfty_;
            // Volatility of correlation
            double dSigma_;
            
        public:
            StochCorrel(double dLambda, double dRhoInfty, double dSigma, double dRho0);
            
            // returns the drift part of the equation, i.e. mu(t, x_t)
            virtual double drift(double dt, double dx) const;
            
            // returns the diffusion part of the equation, i.e. sigma(t,x_t)
            virtual double diffusion(double dt, double dx) const;
            
            // returns the expectation of the process after a time interval
            // returns E(x_{t_0 + delta t} | x_{t_0} = x_0) since it is Markov.
            // By default, it returns the Euler approximation defined by
            // x_0 + mu(t_0, x_0) delta t.
            
            // no term-structure
            virtual double expectation(double t0, double x0, double dt) const;
            
            // returns the variance of the process after a time interval
            // returns Var(x_{t_0 + Delta t} | x_{t_0} = x_0).
            // By default, it returns the Euler approximation defined by
            // sigma(t_0, x_0)^2 \Delta t .
            
            // no term-structure
            virtual double variance(double t0, double x0, double dt) const;
            
        };
    }
}

#endif /* defined(__CVATools__StochCorrel__) */
