//
//  SVIParameters.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 17/06/13.
//
//

#include "SVIParameters.h"
#include <cmath>

SVIParameters::SVIParameters()
{}

SVIParameters::~SVIParameters()
{}

double SVIParameters::Volatility(double k) const
{
    return sqrt(dA_ + dB_ * (dRho_ * (k - dM_) + sqrt((k - dM_) * (k - dM_) + dSigma_ * dSigma_)));
}

double SVIParameters::Variance(double k, double t) const
{
    double dVol = Volatility(k);
    return dVol * dVol * t;
}

void SVIParameters::Calibrate(const std::map<long, std::map<double, double> > &sVolSurface)
{
// to be implemented
}