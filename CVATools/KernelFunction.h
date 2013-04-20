//
//  KernelFunction.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 20/04/13.
//
//

#ifndef CVATools_KernelFunction_h
#define CVATools_KernelFunction_h

class KernelFunction {
protected:
    double dh_; // bandwidth
    
public:
    KernelFunction(double dh);
    virtual double k(double u) const=0;
};

#endif
