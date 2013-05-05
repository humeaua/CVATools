//
//  GaussianKernel.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 20/04/13.
//
//

#include "GaussianKernel.h"
#include <cmath>

GaussianKernel::GaussianKernel(double dh) : KernelFunction(dh)
{}

double GaussianKernel::k(double u) const
{
    // I dropped the \frac{1}{\sqrt{2\pi}} because it will simplify itself when doing the ratio
    return exp(-0.5 * u * u);
}

void GaussianKernel::SetOptimalBandwidth(std::size_t iNObervations, std::size_t iDimension)
{
    //  Compute the correct constant for the minimization of the MISE criterion
    dh_ = 1.0 / pow(iNObervations, 1.0 / (4.0 + iDimension));
}