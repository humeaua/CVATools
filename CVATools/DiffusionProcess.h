//
//  DiffusionProcess.h
//  FinanceTools
//
//  Created by Alexandre HUMEAU on 28/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef FinanceTools_DiffusionProcess_h
#define FinanceTools_DiffusionProcess_h

#include <map>
#include <vector>
#include "SimulationData.h"

namespace Finance
{
    namespace Processes
    {
        class DiffusionProcess
        {
        public:
            DiffusionProcess(double x0, bool bFloorSimulation, bool bStartFromFloor, bool bCapSimulation, bool bStartFromCap, double dCap, double dFloor);
            
            double getx0() const;
            
            // returns the drift part of the equation, i.e. mu(t, x_t)
            virtual double drift(double dt, double dx) const = 0;
            
            // returns the diffusion part of the equation, i.e. sigma(t,x_t)
            virtual double diffusion(double dt, double dx) const = 0;
            
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
            
            // return the standard deviation of the process after a time interval
            // returns stdev(x_{t_0 + Delta t} | x_{t_0} = x_0).
            // By default, it returns the Euler approximation defined by
            // sigma(t_0, x_0) sqrt(\Delta t) .
            virtual double stdev(double t0, double x0, double dt) const;
            
            virtual Utilities::SimulationData simulate(std::vector<double> & dDates, std::size_t iNPaths, long long lSeed) const;
            
        protected:
            double dX0_;
            bool bFloorSimulation_;
            bool bStartFromFloor_;
            bool bCapSimulation_;
            bool bStartFromCap_;
            
            double dCap_;
            double dFloor_;
        };
    }
}

#endif
