//
//  SquareRoot.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 17/03/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef CVATools_SquareRoot_h
#define CVATools_SquareRoot_h

#include "DiffusionProcess.h"

//  The Ornstein Ulhenbeck process is defined as below
//  dX_t = a(b-X_t)dt + \sigma \sqrt{X_t} dW_t

//  The Feller condition states that if \sigma^2 < 2 a b, the process does not touch 0

namespace Finance
{
    namespace Processes
    {
        class SquareRoot : public DiffusionProcess
        {
        protected:
            double dA_, dB_, dSigma_;
            
        private:
            virtual double NonCentralityParameter(double dt) const;
            
        public:
            SquareRoot(double dA, double dB, double dSigma, double dX0);
            
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
            
            //  Simulation method
            virtual Utilities::SimulationData simulate(std::vector<double> & dDates, std::size_t iNPaths, long long lSeed) const;
        };
    }
}

#endif
