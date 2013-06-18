//
//  SVIParameters.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 17/06/13.
//
//

#include "SVIParameters.h"
#include <cmath>
#include "InterExtrapolation.h"

SVIParameters::SVIParameters()
{}

SVIParameters::~SVIParameters()
{}

double SVIParameters::Volatility(double k, double t) const
{
    // interpolate linearly the factors in time
    Utilities::Interp::InterExtrapolationType eInterpType = Utilities::Interp::LIN;
    Utilities::Interp::InterExtrapolation1D sInterpA(dExpiries_, dA_, eInterpType), sInterpB(dExpiries_, dB_, eInterpType), sInterpRho(dExpiries_, dRho_, eInterpType), sInterpM(dExpiries_, dM_, eInterpType), sInterpSigma(dExpiries_, dSigma_, eInterpType);
    
    double dA = sInterpA.Interp1D(t), dB = sInterpB.Interp1D(t), dRho = sInterpRho.Interp1D(t), dM = sInterpM.Interp1D(t), dSigma = sInterpSigma.Interp1D(t);
    
    return sqrt(dA + dB * (dRho * (k - dM) + sqrt((k - dM) * (k - dM) + dSigma * dSigma)));
}

double SVIParameters::Variance(double k, double t) const
{
    double dVol = Volatility(k,t);
    return dVol * dVol * t;
}

void SVIParameters::Calibrate(const std::map<long, std::map<double, double> > &sVolSurface)
{
    //  first add expiries in the vector
    for (std::map<long, std::map<double, double> >::const_iterator it = sVolSurface.begin() ; it != sVolSurface.end(); ++it)
    {
        dExpiries_.push_back(it->first);
    }
    // to be implemented
    
}