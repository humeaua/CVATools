//
//  SchobelZhu.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 11/07/14.
//
//

#ifndef __CVATools__SchobelZhu__
#define __CVATools__SchobelZhu__

#include <iostream>
#include "StochVol.h"

namespace SLV
{
    class SchobelZhu : public StochVol
    {
    public:
        // returns the expectation of the process after a time interval
        // returns E(Sigma_{t_0 + delta t} | Sigma_{t_0} = Sigma_0) since it is Markov.
        // By default, it returns the Euler approximation
        virtual double expectation(double t0, double Sigma0, double dt) const;
        
        // returns the variance of the process after a time interval
        // returns Var(Sigma_{t_0 + Delta t} | Sigma_{t_0} = Sigma_0).
        // By default, it returns the Euler approximation
        virtual double variance(double t0, double Sigma0, double dt) const;
        
        //  returns the conditional expectation of the square of the stoch that appear in the Dupire Formula (markovian projection theorem)
        virtual double conditionalExpectation(double t0, double Sigma0, double S0) const;
        
        virtual StochVol * clone() const;
        
        virtual double MeanReversionLevel(double t0) const;
    private:
        double m_MRSpeed;
        double m_VolVol;
    };
}

#endif /* defined(__CVATools__SchobelZhu__) */
