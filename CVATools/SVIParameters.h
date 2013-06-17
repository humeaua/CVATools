//
//  SVIParameters.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 17/06/13.
//
//

#ifndef __CVATools__SVIParameters__
#define __CVATools__SVIParameters__

#include <iostream>
#include <map>

class SVIParameters {
protected:
    double dA_, dB_, dRho_, dM_, dSigma_;
    
public:
    SVIParameters();
    virtual ~SVIParameters();

    virtual double Volatility(double k) const;
    virtual double Variance(double k, double t) const;

    virtual void Calibrate(const std::map<long, std::map<double, double> > & sVolSurface);
};

#endif /* defined(__CVATools__SVIParameters__) */
