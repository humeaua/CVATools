//
//  OrnsteinUhlenbeck.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 16/03/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef CVATools_OrnsteinUhlenbeck_h
#define CVATools_OrnsteinUhlenbeck_h

#include "DiffusionProcess.h"

//  The Ornstein Ulhenbeck process is defined as below
//  dX_t = a(b-X_t)dt + \sigma dW_t

namespace Finance
{
    namespace Processes
    {
        
#ifndef MEANREVERSIONTHRESHOLD
#define MEANREVERSIONTHRESHOLD 1e-07
#endif
        
        class OrnsteinUhlenbeck : public DiffusionProcess
        {
        protected:
            
            double dA_, dB_, dSigma_;
            
        public:
            OrnsteinUhlenbeck(double dA, double dB, double dSigma, double dX0, long long & lSeed);
            
            virtual double drift(double dt, double dx) const;
            virtual double diffusion(double dt, double dx) const;
            
            // returns the expectation of the process after a time interval
            // returns E(x_{t_0 + delta t} | x_{t_0} = x_0) since it is Markov.
            
            // no term-structure
            virtual double expectation(double t0, double x0, double dt) const;
            
            // returns the variance of the process after a time interval
            // returns Var(x_{t_0 + Delta t} | x_{t_0} = x_0).
            
            // no term-structure
            virtual double variance(double t0, double x0, double dt) const;
        };
    }
}

#endif
