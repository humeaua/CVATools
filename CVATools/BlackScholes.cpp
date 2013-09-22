//
//  BlackScholes.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 27/03/13.
//
//

#include "BlackScholes.h"
#include <cmath>
#include <tr1/random>

namespace Finance
{
    namespace Processes
    {
        BlackScholes::BlackScholes(double dDrift, double dVol, double dX0) : dDrift_(dDrift), dVol_(dVol), DiffusionProcess(dX0, false, false, false, false, std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity())
        {}
        
        BlackScholes::~BlackScholes()
        {}
        
        double BlackScholes::drift(double dt, double dx) const
        {
            return dDrift_ * dx;
        }
        
        double BlackScholes::diffusion(double dt, double dx) const
        {
            return dVol_ * dx;
        }
        
        double BlackScholes::expectation(double t0, double x0, double dt) const
        {
            return x0 * exp(dDrift_ * dt);
        }
        
        double BlackScholes::variance(double t0, double x0, double dt) const
        {
            return exp((2. * dDrift_+ dVol_ * dVol_)* dt) * (exp(dVol_ * dVol_ * dt) - 1);
        }
        
        //  return a simulation data of the simulated path for the diffusion process
        
        Utilities::SimulationData BlackScholes::simulate(std::vector<double> &dDates, std::size_t iNPaths, long long lSeed) const
        {
            std::size_t iNDates = dDates.size();
            Utilities::SimulationData sResult(iNPaths, iNDates);
            
            std::tr1::ranlux64_base_01 eng; // core engine class
            eng.seed(lSeed);
            std::tr1::normal_distribution<double> dist(0.0,1.0);
            //double dDate0 = dDates[0];
            sResult.AddDate(dDates[0]);
            for (std::size_t iPath = 0 ; iPath < iNPaths ; ++iPath)
            {
                double dOldValue = dX0_;
                //sResult.Put(dDate0, iPath, dOldValue);
                sResult(iPath, 0) = dOldValue;
                for (std::size_t iDate = 1 ; iDate < iNDates ; ++iDate)
                {
                    double t0 = dDates[iDate - 1], dt = dDates[iDate] - t0;
                    sResult.AddDate(dDates[iDate]);
                    dOldValue *= exp((dDrift_ - dVol_ * dVol_ * 0.5) * dt + dVol_ * sqrt(dt) * dist(eng));
                    if (bFloorSimulation_ && dOldValue < 0.0)
                    {
                        //sResult.Put(dDates[iDate], iPath, 0.0);
                        sResult(iPath, iDate) = 0.0;
                        if (bStartFromFloor_)
                        {
                            dOldValue = 0.0;
                        }
                    }
                    else
                    {
                        //sResult.Put(dDates[iDate], iPath, dOldValue);
                        sResult(iPath, iDate) = dOldValue;
                    }
                }
            }
            return sResult;
        }
    }
}