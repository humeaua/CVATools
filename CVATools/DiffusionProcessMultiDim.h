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
#include "Type.h"
#include "SimulationDataMultiDim.h"

class DiffusionProcessMultiDim
{
protected:
    std::size_t iNDimensions_;
    Matrix sCorrelationMatrix_;
    DVector dX0_;
public:
    DiffusionProcessMultiDim(std::size_t iNDimension, const Matrix & sCorrelationMatrix, const DVector & dX0);
    template <size_t iDim>
    DiffusionProcessMultiDim(double dCorrelationMatrix[iDim][iDim], const DVector & dX0);
    
    virtual ~DiffusionProcessMultiDim();
    
    //  MultiDimensional Drift drift
    virtual DVector MultiDrift(double dt, DVector dx) const = 0;
    
    //  MultiDimensional volatility vector
    virtual DVector MultiVol(double dt, DVector dx) const = 0;
    
    //  MultiDimensional Expectation
    virtual DVector MultiExpectation(double t0, DVector dx, double dt) const;
    
    //  MultiDimensional Variance
    virtual Matrix MultiVariance(double t0, DVector dx, double dt) const;
    
    //  Simulation method
    virtual SimulationDataMultiDim simulate(std::vector<double> & dDates, std::size_t iNPaths, long long lSeed) const;
    
    //  Add a simulation method for homogeneous processes
};

#endif
