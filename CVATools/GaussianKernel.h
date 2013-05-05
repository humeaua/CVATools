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

class GaussianKernel : public KernelFunction {
    
public:
    GaussianKernel(double dh);
    virtual double k(double u) const;
    
    virtual void SetOptimalBandwidth(std::size_t iNObervations, std::size_t iDimension);
};

#endif
