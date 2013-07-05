//
//  GaussianKernel.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 20/04/13.
//
//

#ifndef CVATools_GaussianKernel_h
#define CVATools_GaussianKernel_h

#include "KernelFunction.h"

namespace Maths
{    
    class GaussianKernel : public KernelFunction
    {
    public:
        GaussianKernel(double dh, double dEpsRegression);
        virtual double k(double u) const;
        
        virtual void SetOptimalBandwidth(const std::vector<double> & dX, std::size_t iNObervations, std::size_t iDimension = 1);
    };
}

#endif
