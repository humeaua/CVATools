//
//  SimulatedProcessMultiDim.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 30/01/14.
//
//

#ifndef __CVATools__SimulatedProcessMultiDim__
#define __CVATools__SimulatedProcessMultiDim__

#include <iostream>
#include <tr1/random>
#include "SimulationDataMultiDim.h"

namespace Finance
{
    namespace Processes
    {
        class SimulatedProcessMultiDim
        {
        protected:
            //  make the engine mutable because the methods are marked const
            //  Actually not very great, would need a proper fix
            mutable std::tr1::ranlux64_base_01 m_eng;
        public:
            SimulatedProcessMultiDim(long long & lSeed);
            virtual Utilities::SimulationDataMultiDim simulate(const std::vector<double> & dDates,
                                                       std::size_t iNPaths,
                                                       long long& lSeed) const = 0;
            
            //virtual std::vector<double> simulate1path(const std::vector<double> & dDates,
            //                                          long long& lSeed) const = 0;
            
            //virtual std::vector<double> Generate1Step(double t0,
            //                                          double x0,
            //                                          double dt,
            //                                          std::size_t iNPaths,
            //                                          long long & lSeed) const = 0;
            
            //virtual double Generate1(double t0,
            //                         double x0,
            //                         double dt,
            //                         long long & lSeed) const = 0;
        };
    }
}

#endif /* defined(__CVATools__SimulatedProcessMultiDim__) */
