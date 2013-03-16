//
//  OrnsteinUhlenbeck.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 16/03/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "OrnsteinUhlenbeck.h"

OrnsteinUhlenbeck::OrnsteinUhlenbeck() : dA_(0.0), dB_(0.0), dSigma_(0.0)
{}

OrnsteinUhlenbeck::OrnsteinUhlenbeck(double dA, double dB, double dSigma, double dX0) : dA_(dA), dB_(dB), dSigma_(dSigma), DiffusionProcess(dX0)
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
