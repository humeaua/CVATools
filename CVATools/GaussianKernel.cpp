//
//  GaussianKernel.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 20/04/13.
//
//

#include "GaussianKernel.h"
#include <cmath>
#include "Statistics.h"

namespace Maths
{
    GaussianKernel::GaussianKernel(double dh, double dEpsRegression) : KernelFunction(dh, dEpsRegression)
    {}
    
    double GaussianKernel::k(double u) const
    {
        // I dropped the \frac{1}{\sqrt{2\pi}} because it will simplify itself when doing the ratio
        return exp(-0.5 * u * u);
    }
    
    void GaussianKernel::SetOptimalBandwidth(const std::vector<double> & dX, std::size_t iNObervations, std::size_t iDimension)
    {
        //  Compute the correct constant for the minimization of the MISE criterion
        Statistics sStats;
        
        //  see http://en.wikipedia.org/wiki/Kernel_density_estimation for the correct formula
        dh_ = pow(4.0 / (3.0 *iNObervations), 1.0 / (4.0 + iDimension)) * sStats.StandardDeviation(dX);
    }
}