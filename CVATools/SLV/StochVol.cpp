//
//  StochVol.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 11/07/14.
//
//

#include "StochVol.h"
#include "Exception.h"

namespace SLV
{
    // returns the expectation of the process after a time interval
    // returns E(Sigma_{t_0 + delta t} | Sigma_{t_0} = Sigma_0) since it is Markov.
    // By default, it returns the Euler approximation
    double StochVol::expectation(double t0, double Sigma0, double dt) const
    {
        throw EXCEPTION("Method not implemented in abstract class. Use derived classes");
    }
    
    // returns the variance of the process after a time interval
    // returns Var(Sigma_{t_0 + Delta t} | Sigma_{t_0} = Sigma_0).
    // By default, it returns the Euler approximation
    double StochVol::variance(double t0, double Sigma0, double dt) const
    {
        throw EXCEPTION("Method not implemented in abstract class. Use derived classes");
    }
    
    //  returns the conditional expectation of the square of the stoch that appear in the Dupire Formula (markovian projection theorem)
    double StochVol::conditionalExpectation(double t0, double Sigma0, double S0) const
    {
        throw EXCEPTION("Method not implemented in abstract class. Use derived classes");
    }
    
    StochVol * StochVol::clone() const
    {
        throw EXCEPTION("Method not implemented in abstract class. Use derived classes");
    }
    
    const RatePtr & StochVol::GetDomUnd() const
    {
        return m_DomUnd;
    }
    
    void StochVol::SetDomUnd(const RatePtr &domUnd)
    {
        m_DomUnd = domUnd;
    }
}