//
//  DiffusionProcessMultiDim.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 28/03/13.
//
//

#ifndef CVATools_DiffusionProcessMultiDim_h
#define CVATools_DiffusionProcessMultiDim_h

#include "DiffusionProcess.h"
#include "Matrix.h"
#include <list>
#include "StochProcessSimulation.h"
#include "SimulationDataMultiDim.h"
#include "SimulatedProcessMultiDim.h"

namespace Finance
{
    namespace Processes
    {
        class DiffusionProcessMultiDim : public SimulatedProcessMultiDim
        {
        protected:
            std::size_t iNDimensions_;
            Utilities::Matrix<double> sCorrelationMatrix_;
            std::vector<double> dX0_;
            std::vector<StochProcessSimulation> sSimulationParams_;
        public:
            DiffusionProcessMultiDim(std::size_t iNDimension, const Utilities::Matrix<double> & sCorrelationMatrix, const std::vector<double> & dX0, const std::vector<StochProcessSimulation>& sSimulationParams, long long & lSeed);
            template <size_t iDim>
            DiffusionProcessMultiDim(double dCorrelationMatrix[iDim][iDim], const std::vector<double> & dX0);
            
            virtual ~DiffusionProcessMultiDim();
            
            //  MultiDimensional Drift drift
            virtual std::vector<double> MultiDrift(double dt, std::vector<double> dx) const = 0;
            
            //  MultiDimensional volatility vector
            virtual std::vector<double> MultiVol(double dt, std::vector<double> dx) const = 0;
            
            //  MultiDimensional Expectation
            virtual std::vector<double> MultiExpectation(double t0, std::vector<double> dx, double dt) const;
            
            //  MultiDimensional Variance
            virtual Utilities::Matrix<double> MultiVariance(double t0, const std::vector<double> &dx, double dt) const;
            
            //  Simulation method
            virtual Utilities::SimulationDataMultiDim simulate(const std::vector<double> & dDates, std::size_t iNPaths, long long& lSeed) const;
            
            //  Add a simulation method for homogeneous processes
        };
    }
}

#endif
