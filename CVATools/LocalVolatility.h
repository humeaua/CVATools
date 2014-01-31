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
#include <functional>

/*
 Implementation of a local volatility class
 
 dS_t / S_t = drift dt + \sigma(t,S_t) dW_t
 
 */

namespace Utilities
{
    namespace Processes
    {
        double zero(double, double);
        double zero(double, double) {return 0.0;};
        
        class LocalVolatility : public Finance::Processes::DiffusionProcess
        {
        protected:
            //std::tr1::function<double (double, double)> SigmaLoc0;
        public:
            LocalVolatility(double x0, long long & lSeed);
            
            virtual double SigmaLoc(double t, double dS) const = 0;
            
            virtual SimulationData simulate(const std::vector<double> & dDates, std::size_t iNPaths) const;
        };
    }
}

#endif /* defined(__CVATools__LocalVolatility__) */
