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

SquareRoot::SquareRoot() : DiffusionProcess(), dA_(0.0), dB_(0.0), dSigma_(0.0)
{}

SquareRoot::SquareRoot(double dA, double dB, double dSigma, double dX0) : DiffusionProcess(dX0, true), dA_(dA), dB_(dB), dSigma_(dSigma)
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
    return dSigma_ * dSigma_ * x0 * dt;
}