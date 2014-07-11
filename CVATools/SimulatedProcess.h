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
#include <tr1/random>
#include <tr1/memory>

namespace Finance
{
    namespace Processes
    {
        //  this class implements a simulated process with all the derived class
        class SimulatedProcess
        {
        protected:
            //  make the engine mutable because the methods are marked const
            //  Actually not very great, would need a proper fix
            std::tr1::shared_ptr<std::tr1::ranlux64_base_01> m_eng;
        public:
            SimulatedProcess(long long & lSeed);
            virtual Utilities::SimulationData simulate(const std::vector<double> & dDates,
                                                       std::size_t iNPaths) const = 0;
            
            virtual std::vector<double> simulate1path(const std::vector<double> & dDates) const = 0;
            
            virtual std::vector<double> Generate1Step(double t0,
                                                      double x0,
                                                      double dt,
                                                      std::size_t iNPaths) const = 0;
            
            virtual double Generate1(double t0,
                                     double x0,
                                     double dt) const = 0;
        };
    }
}

#endif /* defined(__CVATools__SimulatedProcess__) */
