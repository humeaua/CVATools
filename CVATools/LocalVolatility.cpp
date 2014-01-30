//
//  LocalVolatility.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 23/06/13.
//
//

#include "LocalVolatility.h"
#include <tr1/random>

namespace Utilities
{
    namespace Processes
    {
        LocalVolatility::LocalVolatility(double S0, long long & lSeed) : DiffusionProcess(S0, false, false, false, false, std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity(), lSeed)
        {}
        
        //  return a simulation data of the simulated path for the diffusion process
        
        SimulationData LocalVolatility::simulate(const std::vector<double> &dDates, std::size_t iNPaths) const
        {
            std::size_t iNDates = dDates.size();
            SimulationData sResult(iNPaths, iNDates);
            
            std::tr1::normal_distribution<double> dist(0.0,1.0);
            double dOldValue, dDrift, t0, dt, dVol;
            // Add dates first because path-by-path simulations (don't know why)
            for (std::size_t iDate = 0 ; iDate < iNDates ; ++iDate)
            {
                sResult.AddDate(dDates.at(iDate));
            }
            for (std::size_t iPath = 0 ; iPath < iNPaths ; ++iPath)
            {
                dOldValue = dX0_;
                sResult(iPath, 0) = dOldValue;
                for (std::size_t iDate = 1 ; iDate < iNDates ; ++iDate)
                {
                    t0 = dDates.at(iDate - 1);
                    dt = dDates.at(iDate) - t0;
                    dDrift = drift(t0, dOldValue);
                    dVol = SigmaLoc(t0, dOldValue);
                    dOldValue *= exp((dDrift - dVol  * dVol * 0.5) * dt + dVol * sqrt(dt) * dist(*m_eng));
                    
                    sResult(iPath, iDate) = dOldValue;
                }
            }
            return sResult;
        }
    }
}