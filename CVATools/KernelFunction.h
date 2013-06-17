//
//  KernelFunction.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 20/04/13.
//
//

#ifndef CVATools_KernelFunction_h
#define CVATools_KernelFunction_h

#include <iostream>
#include <vector>

class KernelFunction {
protected:
    double dh_; // bandwidth
    double dEpsRegression_; 
    
public:
    KernelFunction(double dh, double dEpsRegression);
    virtual double k(double u) const = 0;
    
    virtual void SetOptimalBandwidth(const std::vector<double>& dX, std::size_t iNObervations, std::size_t iDimension) = 0;
    virtual void SetBandwidth(double dh);
    
    virtual double Estimate(const std::vector<std::pair<double, double> > & dXY, double dX) const;
    virtual double Estimate(const std::vector<std::pair<std::vector<double>, double> > & dXY, const std::vector<double> & dX) const;

};

#endif
