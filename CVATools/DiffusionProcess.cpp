//
//  DiffusionProcess.cpp
//  FinanceTools
//
//  Created by Alexandre HUMEAU on 28/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "DiffusionProcess.h"

/**********************************************************************************
 General diffusion process classes
 This class describes a stochastic process governed by dx(t) = mu(t, x(t))dt +
 sigma(t, x(t))dz(t).
 *********************************************************************************/

namespace Finance
{
    namespace Processes
    {
        DiffusionProcess::DiffusionProcess(double dX0, bool bFloorSimulation, bool bStartFromFloor, bool bCapSimulation, bool bStartFromCap, double dCap, double dFloor, long long & lSeed) : dX0_(dX0), StochProcessSimulation(bFloorSimulation, bStartFromFloor, bCapSimulation, bStartFromCap, dCap, dFloor), SimulatedProcess(lSeed)
        {}
        
        DiffusionProcess::DiffusionProcess(const StochProcessSimulation & SimulationParams, long long & lSeed) : SimulatedProcess(lSeed), StochProcessSimulation(SimulationParams)
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
        Utilities::SimulationData DiffusionProcess::simulate(const std::vector<double> &dDates, std::size_t iNPaths) const
        {
            std::vector<std::vector<double> > dData(iNPaths, std::vector<double>(dDates.size(), 0.0));
            
            for (std::size_t iPath = 0 ; iPath < iNPaths ; ++iPath)
            {
                dData[iPath] = simulate1path(dDates);
            }
            
            Utilities::SimulationData result(dData, dDates);
            return result;
        }
        
        std::vector<double> DiffusionProcess::simulate1path(const std::vector<double> &dDates) const
        {
            std::size_t iNDates = dDates.size();
            std::vector<double> dResult(iNDates, dX0_);
            std::tr1::normal_distribution<double> dist(0.0,1.0);
            
            double dOldValue = dX0_;
            for (std::size_t iDate = 1 ; iDate < iNDates ; ++iDate)
            {
                double t0 = dDates[iDate - 1], dt = dDates[iDate] - t0;
                dOldValue = expectation(t0, dOldValue, dt) + stdev(t0, dOldValue, dt) * dist(*m_eng);
                if (bFloorSimulation_ && dOldValue < dFloor_)
                {
                    dResult[iDate] = dFloor_;
                    if (bStartFromFloor_)
                    {
                        dOldValue = dFloor_;
                    }
                }
                else if (bCapSimulation_ && dOldValue > dCap_)
                {
                    dResult[iDate] = dCap_;
                    if (bStartFromCap_)
                    {
                        dOldValue = dCap_;
                    }
                }
                else
                {
                    dResult[iDate] = dOldValue;
                }
            }
            return dResult;
        }
        
        std::vector<double> DiffusionProcess::Generate1Step(double t0, double x0, double dt,
                                          std::size_t iNPaths) const
        {
            std::vector<double> dResults;
            for (std::size_t i = 0 ; i < iNPaths ; ++i)
            {
                dResults.push_back(Generate1(t0, x0, dt));
            }
            return dResults;
        }
        
        double DiffusionProcess::Generate1(double t0, double x0, double dt) const
        {
            std::tr1::normal_distribution<double> dist(expectation(t0, x0, dt),stdev(t0, x0, dt));
            return dist(*m_eng);
        }
    }
}