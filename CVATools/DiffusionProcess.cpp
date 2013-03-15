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

DiffusionProcess::DiffusionProcess() : dX0_(0.0)
{}

DiffusionProcess::DiffusionProcess(double dX0)
{
    dX0_ = dX0;
}

double DiffusionProcess::Getx0() const
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