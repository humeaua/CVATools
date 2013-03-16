//
//  OrnsteinUhlenbeck.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 16/03/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef CVATools_OrnsteinUhlenbeck_h
#define CVATools_OrnsteinUhlenbeck_h

#include "DiffusionProcess.h"

//  The Ornstein Ulhenbeck process is defined as below
//  dX_t = a(b-X_t)dt + \sigma dW_t

class OrnsteinUhlenbeck : public DiffusionProcess {
protected:
    
    double dA_, dB_, dSigma_;
    
public:
    OrnsteinUhlenbeck();
    OrnsteinUhlenbeck(double dA, double dB, double dSigma, double dX0);
    
    virtual ~OrnsteinUhlenbeck();
    
    virtual double drift(double dt, double dx) const;
    virtual double diffusion(double dt, double dx) const;
    
};

#endif
