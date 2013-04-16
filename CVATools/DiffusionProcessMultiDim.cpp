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

DiffusionProcessMultiDim::DiffusionProcessMultiDim(std::size_t iNDimensions, const Matrix & sCorrelationMatrix, const DVector & dX0) : iNDimensions_(iNDimensions), sCorrelationMatrix_(sCorrelationMatrix), dX0_(dX0)
{
    assert(iNDimensions_ == sCorrelationMatrix_.getrows());
    assert(iNDimensions_ == sCorrelationMatrix_.getcols());
}

DiffusionProcessMultiDim::~DiffusionProcessMultiDim()
{}

//  MultiDimensional Expectation
DVector DiffusionProcessMultiDim::MultiExpectation(double t0, DVector dx, double dt) const
{
    assert(dx.size() == iNDimensions_);
    DVector dResult(iNDimensions_), dMultiDrift = MultiDrift(dt, dx);
    for (std::size_t iDim = 0 ; iDim < iNDimensions_ ; ++iDim)
    {
        dResult[iDim] = dx[iDim] + dMultiDrift[iDim];
    }
    return dResult;
}

//  MultiDimensional Variance
Matrix DiffusionProcessMultiDim::MultiVariance(double t0, DVector dx, double dt) const
{
    assert(dx.size() == iNDimensions_);
    Matrix dResult(iNDimensions_, iNDimensions_);
    DVector dMultiVol = MultiVol(dt, dx);
    for (std::size_t iRow = 0 ; iRow < iNDimensions_ ; ++iRow)
    {
        double dSigmai = dMultiVol[iRow];
        //dResult(iRow, iRow) = dSigmai * dSigmai * dt;
        dResult.set(iRow, iRow, dSigmai * dSigmai * dt);
        for (std::size_t iCol = iRow + 1 ; iCol < iNDimensions_ ; ++iCol)
        {
            double dSigmaj = dMultiVol[iCol];
            //dResult(iRow, iCol) = dSigmai * dSigmaj * sCorrelationMatrix_(iRow,iCol) * dt;
            dResult.set(iRow, iCol, dSigmai * dSigmaj * sCorrelationMatrix_(iRow,iCol) * dt);
            //dResult(iCol, iRow) = dResult(iRow,iCol);
            dResult.set(iCol, iRow, dResult(iRow,iCol));
        }
    }
    return dResult;
}

//  Simulation method
SimulationDataMultiDim DiffusionProcessMultiDim::simulate(std::vector<double> & dDates, std::size_t iNPaths, long long lSeed) const
{
    SimulationDataMultiDim sResult;
    std::size_t iNDates = dDates.size();
    
    std::tr1::ranlux64_base_01 eng; // core engine class
    eng.seed(lSeed);
    std::tr1::normal_distribution<double> dist(0.0,1.0);
    
    DVector dOldValues, dRandomNumbers(iNDimensions_);
    for (std::size_t iDate = 1 ; iDate < iNDates ; ++iDate)
    {
        double t0 = dDates[iDate - 1], dt = dDates[iDate] - t0;
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
            Matrix sCovarMatrix = MultiVariance(t0, dOldValues, dt), sSquareRoot(iNDimensions_, iNDimensions_);
            
            //  Choleski decomposition
            CholeskiDecomposition(sCovarMatrix, sSquareRoot);
            
            DVector dExpectation = MultiExpectation(t0, dOldValues, dt);
            
            //  Generate the random numbers
            for (std::size_t i = 0 ; i < iNDimensions_ ; ++i)
            {
                dRandomNumbers[i] = dist(eng);
            }
            
            DVector dCorrelatedNumbers;
            mult(dCorrelatedNumbers, sSquareRoot, dRandomNumbers);
            
            for (std::size_t i = 0 ; i < iNDimensions_ ; ++i)
            {
                sResult.Put(t0 + dt, iPath, i, dExpectation[i] + dCorrelatedNumbers[i]);
            }
        }
    }
    return sResult;
}