//
//  LocalVolatility.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 23/06/13.
//
//

#include "LocalVolatility.h"
#include <tr1/random>

LocalVolatility::LocalVolatility(double S0) : DiffusionProcess(S0, false, false)
{}

LocalVolatility::~LocalVolatility()
{}

//  return a simulation data of the simulated path for the diffusion process

SimulationData LocalVolatility::simulate(std::vector<double> &dDates, std::size_t iNPaths, long long lSeed) const
{
    SimulationData sResult;
    std::size_t iNDates = dDates.size();
    
    std::tr1::ranlux64_base_01 eng; // core engine class
    eng.seed(lSeed);
    std::tr1::normal_distribution<double> dist(0.0,1.0);
    double dDate0 = dDates[0], dOldValue, dDrift, t0, dt, dVol;
    for (std::size_t iPath = 0 ; iPath < iNPaths ; ++iPath)
    {
        dOldValue = dX0_;
        sResult.Put(dDate0, iPath, dOldValue);
        for (std::size_t iDate = 1 ; iDate < iNDates ; ++iDate)
        {
            t0 = dDates[iDate - 1];
            dt = dDates[iDate] - t0;
            dDrift = drift(t0, dOldValue);
            dVol = SigmaLoc(t0, dOldValue);
            dOldValue *= exp((dDrift - dVol  * dVol * 0.5) * dt + dVol * sqrt(dt) * dist(eng));
            if (bFloorSimulationAtZero_ && dOldValue < 0.0)
            {
                sResult.Put(dDates[iDate], iPath, 0.0);
                if (bStartFrom0AfterFloor_)
                {
                    dOldValue = 0.0;
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