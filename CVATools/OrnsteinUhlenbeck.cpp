//
//  OrnsteinUhlenbeck.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 16/03/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "OrnsteinUhlenbeck.h"
#include <cmath>

OrnsteinUhlenbeck::OrnsteinUhlenbeck() : dA_(0.0), dB_(0.0), dSigma_(0.0)
{}

OrnsteinUhlenbeck::OrnsteinUhlenbeck(double dA, double dB, double dSigma, double dX0) : dA_(dA), dB_(dB), dSigma_(dSigma), DiffusionProcess(dX0, false, false)
{}

OrnsteinUhlenbeck::~OrnsteinUhlenbeck()
{}

double OrnsteinUhlenbeck::drift(double dt, double dx) const
{
    return dA_ * (dB_ - dx);
}

double OrnsteinUhlenbeck::diffusion(double dt, double dx) const
{
    return dSigma_;
}

// returns the expectation of the process after a time interval
// returns E(x_{t_0 + delta t} | x_{t_0} = x_0) since it is Markov.

// no term-structure
double OrnsteinUhlenbeck::expectation(double t0, double x0, double dt) const
{
    return x0 * exp(-dA_ * dt) + dB_ * (1. - exp(-dA_ * dt));
}

// returns the variance of the process after a time interval
// returns Var(x_{t_0 + Delta t} | x_{t_0} = x_0).

// no term-structure
double OrnsteinUhlenbeck::variance(double t0, double x0, double dt) const
{
    if (std::abs(dA_) < MEANREVERSIONTHRESHOLD)
    {
        return dSigma_ * dSigma_ * dt;
    }
    else
    {
        return dSigma_ * dSigma_ * 0.5 * (1 - exp(-2. * dA_ * dt)) / dA_;
    }
}
