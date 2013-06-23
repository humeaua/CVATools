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

SquareRoot::SquareRoot() : DiffusionProcess(), dA_(0.0), dB_(0.0), dSigma_(0.0)
{}

SquareRoot::SquareRoot(double dA, double dB, double dSigma, double dX0) : DiffusionProcess(dX0, true, true), dA_(dA), dB_(dB), dSigma_(dSigma)
{}

SquareRoot::~SquareRoot()
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
    //return dSigma_ * dSigma_ * (dB_ * 0.5 / dA_ + (x0 - dB_) / dA_ * exp(-dA_ * dt) + (dB_ - 2. * dX0_) * 0.5 / dA_ * exp(-2. * dA_ * dt));
    //return dSigma_ * dSigma_ * exp(-dA_ * dt) * x0 *dt;
    return x0 * dSigma_ * dSigma_ * exp(-dA_ * dt) / dA_ * (1 - exp(-dA_ * dt)) + dB_ * dSigma_ * dSigma_ * 0.5 / dA_ * (1 - exp(-dA_ * dt)) * (1 - exp(-dA_ * dt));
}

double SquareRoot::NonCentralityParameter(double dt) const
{
    return 4.0 * dA_ * exp(-dA_ * dt) / (dSigma_ * dSigma_ * (1.0 - exp(-dA_ * dt)));
}

SimulationData SquareRoot::simulate(std::vector<double> & dDates, std::size_t iNPaths, long long lSeed) const
{
    // simulation according to http://www.awdz65.dsl.pipex.com/eqf013_009.pdf
    
    SimulationData sResult;
    std::size_t iNDates = dDates.size();
    
    std::tr1::ranlux64_base_01 eng; // core engine class
    eng.seed(lSeed);
    
    double dDate0 = dDates[0];
    //  initial values 
    for (std::size_t iPath = 0 ; iPath < iNPaths ; ++iPath)
    {
        sResult.Put(dDate0, iPath, dX0_);
    }
    
    double dD = 4 * dA_ * dB_ / (dSigma_ * dSigma_);
    double dOldValue, dNewValue;
    for (std::size_t iDate = 1 ; iDate < iNDates ; ++iDate)
    {
        double t0 = dDates[iDate - 1], dt = dDates[iDate] - t0;
        
        
        for (std::size_t iPath = 0 ; iPath < iNPaths ; ++iPath)
        {
            dOldValue = sResult.Get(t0, iPath);
            std::tr1::poisson_distribution<double> poisson(0.5 * NonCentralityParameter(dt) * dOldValue);
            
            double dNbOfFreedom = poisson(eng);
            std::tr1::gamma_distribution<double> gamma(dNbOfFreedom + 0.5 * dD);
            dNewValue = gamma(eng);
            
            sResult.Put(dDates[iDate], iPath, dNewValue);
        }
    }
    return sResult;
}
