//
//  LocalVolatility.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 23/06/13.
//
//

#include "LocalVolatility.h"
#include <tr1/random>

namespace Finance
{
    namespace Processes
    {
        LocalVolatility::LocalVolatility(double S0, long long & lSeed) : DiffusionProcess(S0, false, false, false, false, std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity(), lSeed)//, SigmaLoc(zero)
        {}
        
        //  return a simulation data of the simulated path for the diffusion process
        
        std::vector<double> LocalVolatility::simulate1path(const std::vector<double> &dDates) const
        {
            std::size_t iNDates = dDates.size();
            std::vector<double> sResult(iNDates);
            
            std::tr1::normal_distribution<double> dist(0.0,1.0);
            double dOldValue, dDrift, t0, dt, dVol;
            
            dOldValue = dX0_;
            sResult.at(0) = dOldValue;
            for (std::size_t iDate = 1 ; iDate < iNDates ; ++iDate)
            {
                t0 = dDates.at(iDate - 1);
                dt = dDates.at(iDate) - t0;
                dDrift = drift(t0, dOldValue);
                dVol = SigmaLoc(t0, dOldValue);
                dOldValue *= exp((dDrift - dVol  * dVol * 0.5) * dt + dVol * sqrt(dt) * dist(*m_eng));
                
                sResult.at(iDate) = dOldValue;
            }
            return sResult;
        }
        
        double LocalVolatility::diffusion(double t, double S) const
        {
            return S * SigmaLoc(t, S);
        }
    }
}