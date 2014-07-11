//
//  SchobelZhu.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 11/07/14.
//
//

#include "SchobelZhu.h"

namespace SLV
{
    // returns the expectation of the process after a time interval
    // returns E(Sigma_{t_0 + delta t} | Sigma_{t_0} = Sigma_0) since it is Markov.
    // By default, it returns the Euler approximation
    double SchobelZhu::expectation(double t0, double Sigma0, double dt) const
    {
        // to be implemented
        return 0.0;
    }
    
    // returns the variance of the process after a time interval
    // returns Var(Sigma_{t_0 + Delta t} | Sigma_{t_0} = Sigma_0).
    // By default, it returns the Euler approximation
    double SchobelZhu::variance(double t0, double Sigma0, double dt) const
    {
        // to be implemented
        return 0.0;
    }
    
    //  returns the conditional expectation of the square of the stoch that appear in the Dupire Formula (markovian projection theorem)
    double SchobelZhu::conditionalExpectation(double t0, double Sigma0, double S0) const
    {
        // to be implemented
        return 0.0;
    }
    
    StochVol * SchobelZhu::clone() const
    {
        return new StochVol(*this);
    }
}