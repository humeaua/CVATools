//
//  DiffusionProcessMultiDim.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 28/03/13.
//
//

#include "DiffusionProcessMultiDim.h"
#include <assert.h>
#include <tr1/random>

namespace Finance
{
    namespace Processes
    {
        DiffusionProcessMultiDim::DiffusionProcessMultiDim(std::size_t iNDimensions, const Utilities::Matrix<double> & sCorrelationMatrix, const std::vector<double>  & dX0, const std::vector<StochProcessSimulation> & sSimulationParams, long long & lSeed) : iNDimensions_(iNDimensions), sCorrelationMatrix_(sCorrelationMatrix), dX0_(dX0), sSimulationParams_(sSimulationParams), SimulatedProcessMultiDim(lSeed)
        {
            assert(iNDimensions_ == sCorrelationMatrix_.getrows());
            assert(iNDimensions_ == sCorrelationMatrix_.getcols());
        }
        
        template <size_t iDim>
        DiffusionProcessMultiDim::DiffusionProcessMultiDim(double dCorrelationMatrix[iDim][iDim], const std::vector<double> & dX0) : iNDimensions_(iDim), dX0_(dX0)
        {
            sCorrelationMatrix_ = Matrix(dCorrelationMatrix, iDim);
        }
        
        DiffusionProcessMultiDim::~DiffusionProcessMultiDim()
        {}
        
        //  MultiDimensional Expectation
        std::vector<double> DiffusionProcessMultiDim::MultiExpectation(double t0, std::vector<double> dx, double dt) const
        {
            assert(dx.size() == iNDimensions_);
            std::vector<double> dResult(iNDimensions_), dMultiDrift = MultiDrift(dt, dx);
            for (std::size_t iDim = 0 ; iDim < iNDimensions_ ; ++iDim)
            {
                dResult.at(iDim) = dx.at(iDim) + dMultiDrift.at(iDim);
            }
            return dResult;
        }
        
        //  MultiDimensional Variance
        Utilities::Matrix<double> DiffusionProcessMultiDim::MultiVariance(double t0, const std::vector<double> & dx, double dt) const
        {
            assert(dx.size() == iNDimensions_);
            Utilities::Matrix<double> dResult(iNDimensions_, iNDimensions_);
            std::vector<double> dMultiVol = MultiVol(dt, dx);
            for (std::size_t iRow = 0 ; iRow < iNDimensions_ ; ++iRow)
            {
                double dSigmai = dMultiVol.at(iRow);
                dResult(iRow, iRow) = dSigmai * dSigmai * dt;
                //dResult.set(iRow, iRow, dSigmai * dSigmai * dt);
                for (std::size_t iCol = iRow + 1 ; iCol < iNDimensions_ ; ++iCol)
                {
                    double dSigmaj = dMultiVol.at(iCol);
                    dResult(iRow, iCol) = dSigmai * dSigmaj * sCorrelationMatrix_(iRow,iCol) * dt;
                    //dResult.set(iRow, iCol, dSigmai * dSigmaj * sCorrelationMatrix_(iRow,iCol) * dt);
                    dResult(iCol, iRow) = dResult(iRow,iCol);
                    //dResult.set(iCol, iRow, dResult(iRow,iCol));
                }
            }
            return dResult;
        }
        
        //  Simulation method
        Utilities::SimulationDataMultiDim DiffusionProcessMultiDim::simulate(const std::vector<double> & dDates, std::size_t iNPaths, long long& lSeed) const
        {
            Utilities::SimulationDataMultiDim sResult;
            std::size_t iNDates = dDates.size();
            
            std::tr1::normal_distribution<double> dist(0.0,1.0);
            
            std::vector<double> dOldValues, dRandomNumbers(iNDimensions_);
            for (std::size_t iDate = 1 ; iDate < iNDates ; ++iDate)
            {
                double t0 = dDates.at(iDate - 1), dt = dDates.at(iDate) - t0;
                for (std::size_t iPath = 0 ; iPath < iNPaths ; ++iPath)
                {
                    if (iDate != 1)
                    {
                        dOldValues = sResult.GetData(dt + t0, iPath);
                    }
                    else
                    {
                        dOldValues = dX0_;
                    }
                    Utilities::Matrix<double> sCovarMatrix = MultiVariance(t0, dOldValues, dt), sSquareRoot(iNDimensions_, iNDimensions_);
                    
                    //  Choleski decomposition
                    CholeskiDecomposition(sCovarMatrix, sSquareRoot);
                    
                    std::vector<double> dExpectation = MultiExpectation(t0, dOldValues, dt);
                    
                    //  Generate the random numbers
                    for (std::size_t i = 0 ; i < iNDimensions_ ; ++i)
                    {
                        dRandomNumbers.at(i) = dist(*m_eng);
                    }
                    
                    std::vector<double> dCorrelatedNumbers;
                    mult(dCorrelatedNumbers, sSquareRoot, dRandomNumbers);
                    
                    for (std::size_t i = 0 ; i < iNDimensions_ ; ++i)
                    {
                        sResult.Put(t0 + dt, iPath, i, dExpectation.at(i) + dCorrelatedNumbers.at(i));
                    }
                }
            }
            return sResult;
        }
    }
}