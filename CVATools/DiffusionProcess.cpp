//
//  DiffusionProcess.cpp
//  FinanceTools
//
//  Created by Alexandre HUMEAU on 28/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "DiffusionProcess.h"
#include <tr1/random>

/**********************************************************************************
 General diffusion process classes
 This class describes a stochastic process governed by dx(t) = mu(t, x(t))dt +
 sigma(t, x(t))dz(t).
 *********************************************************************************/

namespace Finance
{
    namespace Processes
    {
        DiffusionProcess::DiffusionProcess(double dX0, bool bFloorSimulation, bool bStartFromFloor, bool bCapSimulation, bool bStartFromCap, double dCap, double dFloor) : bFloorSimulation_(bFloorSimulation), bStartFromFloor_(bStartFromFloor), dX0_(dX0), bCapSimulation_(bCapSimulation), bStartFromCap_(bStartFromCap), dCap_(dCap), dFloor_(dFloor)
        {}
        
        double DiffusionProcess::getx0() const
        {
            return dX0_;
        }
        
        // returns the expectation of the process after a time interval
        // returns E(x_{t_0 + delta t} | x_{t_0} = x_0) since it is Markov.
        // By default, it returns the Euler approximation defined by
        // x_0 + mu(t_0, x_0) delta t.
        
        double DiffusionProcess::expectation(double t0, double x0, double dt) const
        {
            return x0 + drift(t0, x0) * dt;
        }
        
        // returns the variance of the process after a time interval
        // returns Var(x_{t_0 + Delta t} | x_{t_0} = x_0).
        // By default, it returns the Euler approximation defined by
        // sigma(t_0, x_0)^2 \Delta t .
        
        double DiffusionProcess::variance(double t0, double x0, double dt) const
        {
            double dSigma = diffusion(t0, x0);
            return dSigma * dSigma * dt;
        }
        
        // return the standard deviation of the process after a time interval
        // returns stdev(x_{t_0 + Delta t} | x_{t_0} = x_0).
        // By default, it returns the Euler approximation defined by
        // sigma(t_0, x_0) sqrt(\Delta t) .
        
        double DiffusionProcess::stdev(double t0, double x0, double dt) const
        {
            return sqrt(variance(t0, x0, dt));
        }
        
        //  return a simulation data of the simulated path for the diffusion process
        
        Utilities::SimulationData DiffusionProcess::simulate(std::vector<double> &dDates, std::size_t iNPaths, long long lSeed) const
        {
            Utilities::SimulationData sResult;
            std::size_t iNDates = dDates.size();
            
            std::tr1::ranlux64_base_01 eng; // core engine class
            eng.seed(lSeed);
            std::tr1::normal_distribution<double> dist(0.0,1.0);
            double dDate0 = dDates[0];
            for (std::size_t iPath = 0 ; iPath < iNPaths ; ++iPath)
            {
                double dOldValue = dX0_;
                sResult.Put(dDate0, iPath, dOldValue);
                for (std::size_t iDate = 1 ; iDate < iNDates ; ++iDate)
                {
                    double t0 = dDates[iDate - 1], dt = dDates[iDate] - t0;
                    dOldValue = expectation(t0, dOldValue, dt) + stdev(t0, dOldValue, dt) * dist(eng);
                    if (bFloorSimulation_ && dOldValue < dFloor_)
                    {
                        sResult.Put(dDates[iDate], iPath, dFloor_);
                        if (bStartFromFloor_)
                        {
                            dOldValue = dFloor_;
                        }
                    }
                    else if (bCapSimulation_ && dOldValue > dCap_)
                    {
                        sResult.Put(dDates[iDate], iPath, dCap_);
                        if (bStartFromCap_)
                        {
                            dOldValue = dCap_;
                       }
                    }
                    else
                    {
                        sResult.Put(dDates[iDate], iPath, dOldValue);
                    }
                }
            }
            return sResult;
        }
    }
}