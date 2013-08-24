//
//  BlackScholes.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 27/03/13.
//
//

#ifndef CVATools_BlackScholes_h
#define CVATools_BlackScholes_h

#include "DiffusionProcess.h"

namespace Finance
{
    namespace Processes
    {
        class BlackScholes : public Finance::Processes::DiffusionProcess
        {
        protected:
            double dDrift_, dVol_;
            
        public:
            BlackScholes(double dDrift, double dVol, double dX0);
            
            virtual ~BlackScholes();
            
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
            
            virtual Utilities::SimulationData simulate(std::vector<double> &dDates, std::size_t iNPaths, long long lSeed) const;
        };
    }
}

#endif
