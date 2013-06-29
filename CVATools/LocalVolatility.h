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
 
 dS_t / S_t = drift dt + \sigma(t,S_t) dW_t
 
 */

class LocalVolatility : public DiffusionProcess {
protected:
    
public:
    LocalVolatility(double x0);
    virtual ~LocalVolatility();
    
    virtual double SigmaLoc(double t, double dS) const = 0;
    
    virtual SimulationData simulate(std::vector<double> & dDates, std::size_t iNPaths, long long lSeed) const;
};

#endif /* defined(__CVATools__LocalVolatility__) */
