//
//  SquareRoot.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 17/03/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "SquareRoot.h"
#include <cmath>
#include <tr1/random>

namespace Finance
{
    namespace Processes
    {
        SquareRoot::SquareRoot(double dA, double dB, double dSigma, double dX0, long long & lSeed) : DiffusionProcess(dX0, true, true, false, false, std::numeric_limits<double>::infinity(), 0.0, lSeed), dA_(dA), dB_(dB), dSigma_(dSigma)
        {}
        
        double SquareRoot::drift(double dt, double dx) const
        {
            return dA_ * (dB_ - dx);
        }
        
        double SquareRoot::diffusion(double dt, double dx) const
        {
            return dSigma_ * sqrt(dx);
        }
        
        // returns the expectation of the process after a time interval
        // returns E(x_{t_0 + delta t} | x_{t_0} = x_0) since it is Markov.
        
        // no term-structure
        double SquareRoot::expectation(double t0, double x0, double dt) const
        {
            return x0 * exp(-dA_ * dt) + dB_ * (1. - exp(-dA_ * dt));
        }
        
        // returns the variance of the process after a time interval
        // returns Var(x_{t_0 + Delta t} | x_{t_0} = x_0).
        
        // no term-structure
        double SquareRoot::variance(double t0, double x0, double dt) const
        {
            return x0 * dSigma_ * dSigma_ * exp(-dA_ * dt) / dA_ * (1 - exp(-dA_ * dt)) + dB_ * dSigma_ * dSigma_ * 0.5 / dA_ * (1 - exp(-dA_ * dt)) * (1 - exp(-dA_ * dt));
        }
        
        double SquareRoot::NonCentralityParameter(double dt) const
        {
            return 4.0 * dA_ * exp(-dA_ * dt) / (dSigma_ * dSigma_ * (1.0 - exp(-dA_ * dt)));
        }
        
        Utilities::SimulationData SquareRoot::simulate(const std::vector<double> & dDates, std::size_t iNPaths) const
        {
            // simulation according to http://www.awdz65.dsl.pipex.com/eqf013_009.pdf
            
            std::size_t iNDates = dDates.size();
            Utilities::SimulationData sResult(iNPaths, iNDates);
            
            sResult.AddDate(dDates[0]);
            //  initial values
            for (std::size_t iPath = 0 ; iPath < iNPaths ; ++iPath)
            {
                sResult(iPath, 0) = dX0_;
            }
            
            double dD = 4 * dA_ * dB_ / (dSigma_ * dSigma_);
            double dOldValue, dNewValue;
            for (std::size_t iDate = 1 ; iDate < iNDates ; ++iDate)
            {
                double t0 = dDates.at(iDate - 1), dt = dDates.at(iDate) - t0;
                sResult.AddDate(dDates[iDate]);
                
                for (std::size_t iPath = 0 ; iPath < iNPaths ; ++iPath)
                {
                    dOldValue = sResult(iPath,iDate - 1);
                    std::tr1::poisson_distribution<double> poisson(0.5 * NonCentralityParameter(dt) * dOldValue);
                    
                    double dNbOfFreedom = poisson(m_eng);
                    // 2.0 * gamma_distribution(0.5 * number of degree of freedom) is a chi-squared distribution with the wanted number of degree of freedom
                    std::tr1::gamma_distribution<double> gamma(dNbOfFreedom + 0.5 * dD);
                    dNewValue = 2.0 * gamma(m_eng) * exp(-dA_ * dt) / NonCentralityParameter(dt);
                    
                    sResult(iPath, iDate) = dNewValue;
                }
            }
            return sResult;
        }
        
        std::vector<double> SquareRoot::simulate1path(const std::vector<double> & dDates) const
        {
            // simulation according to http://www.awdz65.dsl.pipex.com/eqf013_009.pdf
            
            std::size_t iNDates = dDates.size();
            std::vector<double> sResult(iNDates, 0.0);
            
            sResult.front() = dX0_;
            
            double dD = 4 * dA_ * dB_ / (dSigma_ * dSigma_);
            double dOldValue, dNewValue;
            for (std::size_t iDate = 1 ; iDate < iNDates ; ++iDate)
            {
                double t0 = dDates.at(iDate - 1), dt = dDates.at(iDate) - t0;
                dOldValue = sResult[iDate - 1];
                std::tr1::poisson_distribution<double> poisson(0.5 * NonCentralityParameter(dt) * dOldValue);
                
                double dNbOfFreedom = poisson(m_eng);
                // 2.0 * gamma_distribution(0.5 * number of degree of freedom) is a chi-squared distribution with the wanted number of degree of freedom
                std::tr1::gamma_distribution<double> gamma(dNbOfFreedom + 0.5 * dD);
                dNewValue = 2.0 * gamma(m_eng) * exp(-dA_ * dt) / NonCentralityParameter(dt);
                
                sResult[iDate] = dNewValue;
            }
            return sResult;
        }

    }
}