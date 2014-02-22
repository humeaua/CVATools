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
        BlackScholes::BlackScholes(double dDrift, double dVol, double dX0, long long & lSeed) : dDrift_(dDrift), dVol_(dVol), DiffusionProcess(dX0, false, false, false, false, std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity(), lSeed)
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
        
        std::vector<double> BlackScholes::simulate1path(const std::vector<double> &dDates) const
        {
            std::vector<double> result(dDates.size(), 0.0);
            
            std::tr1::normal_distribution<double> dist(0.0,1.0);
            double dOldValue = dX0_;
            result.at(0) = dOldValue;
            for (std::size_t iDate = 1 ; iDate < dDates.size() ; ++iDate)
            {
                double t0 = dDates.at(iDate - 1), dt = dDates.at(iDate) - t0;
                dOldValue *= exp((dDrift_ - dVol_ * dVol_ * 0.5) * dt + dVol_ * sqrt(dt) * dist(*m_eng));
                if (bFloorSimulation_ && dOldValue < 0.0)
                {
                    result.at(iDate) = 0.0;
                    if (bStartFromFloor_)
                    {
                        dOldValue = 0.0;
                    }
                }
                else
                {
                    result.at(iDate) = dOldValue;
                }
            }
            return result;
        }
    }
}