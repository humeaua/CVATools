//
//  SimulatedProcess.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 30/01/14.
//
//

#ifndef __CVATools__SimulatedProcess__
#define __CVATools__SimulatedProcess__

#include <iostream>
#include "SimulationData.h"

namespace Finance
{
    namespace Processes
    {
        //  this class implements a simulated process with all the derived class
        class SimulatedProcess
        {
        public:
            virtual Utilities::SimulationData simulate(const std::vector<double> & dDates,
                                                       std::size_t iNPaths,
                                                       long long& lSeed) const = 0;
            
            virtual std::vector<double> simulate1path(const std::vector<double> & dDates,
                                                      long long& lSeed) const = 0;
            
            virtual std::vector<double> Generate1Step(double t0,
                                                      double x0,
                                                      double dt,
                                                      std::size_t iNPaths,
                                                      long long & lSeed) const = 0;
            
            virtual double Generate1(double t0,
                                     double x0,
                                     double dt,
                                     long long & lSeed) const = 0;
        };
    }
}

#endif /* defined(__CVATools__SimulatedProcess__) */
