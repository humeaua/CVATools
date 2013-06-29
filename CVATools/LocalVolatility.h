//
//  LocalVolatility.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 23/06/13.
//
//

#ifndef __CVATools__LocalVolatility__
#define __CVATools__LocalVolatility__

#include <iostream>
#include "DiffusionProcess.h"

/*
 Implementation of a local volatility class
 
 dS_t / S_t = r_t dt + \sigma(t,S_t) dW_t
 
 */

class LocalVolatility : public DiffusionProcess {
protected:
    
public:
    virtual double SigmaLoc(double t, double dS) const = 0;
};

#endif /* defined(__CVATools__LocalVolatility__) */
