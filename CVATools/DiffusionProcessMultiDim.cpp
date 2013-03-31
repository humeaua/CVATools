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

DiffusionProcessMultiDim::DiffusionProcessMultiDim(std::size_t iNDimensions, const Matrix & sCorrelationMatrix) : iNDimensions_(iNDimensions), sCorrelationMatrix_(sCorrelationMatrix)
{
    assert(iNDimensions_ == sCorrelationMatrix_.getrows());
    assert(iNDimensions_ == sCorrelationMatrix_.getcols());
}

DiffusionProcessMultiDim::~DiffusionProcessMultiDim()
{
    sCorrelationMatrix_.~Matrix();
}

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
        for (std::size_t iCol = iRow + 1 ; iCol < iNDimensions_ ; ++iCol)
        {
            double dSigmaj = dMultiVol[iCol];
            dResult(iRow, iCol) = dSigmai * dSigmaj * sCorrelationMatrix_(iRow,iCol) * dt;
            dResult(iCol, iRow) = dResult(iRow,iCol);
        }
    }
    return dResult;
}

//  Simulation method
SimulationDataMultiDim DiffusionProcessMultiDim::simulate(std::vector<double> & dDates, std::size_t iNPaths, long long lSeed) const
{
    SimulationDataMultiDim sResult;
    
    return sResult;
}