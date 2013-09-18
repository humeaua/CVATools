//
//  PayoffLinearization.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 20/07/13.
//
//

#include "PayoffLinearization.h"

namespace Maths
{
    PayoffLinearization::PayoffLinearization(std::size_t iNPaths) : iNPaths_(iNPaths)
    {}
    
    Utilities::Matrix PayoffLinearization::ComputeCovarianceMatrix(const std::vector<double> & dFinalUnderlying) const
    {
        Utilities::Matrix sCovarMatrix(2,2);
        double dtemp = 0.0, dX = 0.0, dX2 = 0.0;
        for (std::size_t iPath = 0 ; iPath < iNPaths_ ; ++iPath)
        {
            dtemp = dFinalUnderlying[iPath];
            dX += dtemp;
            dX2 += dtemp * dtemp;
        }
        dX /= iNPaths_;
        dX2 /= iNPaths_;
        
        sCovarMatrix.set(0, 0, 1);
        sCovarMatrix.set(0, 1, dX);
        sCovarMatrix.set(1, 0, dX);
        sCovarMatrix.set(1, 1, dX2);
        
        return sCovarMatrix;
    }
    
    std::pair<double, double> PayoffLinearization::ComputeRegCoefs(const std::vector<double> & dPayoff,
                                                                   const std::vector<double> & dFinalUnderlying) const
    {
        Utilities::Matrix sCovarianceMatrix = ComputeCovarianceMatrix(dFinalUnderlying), sInverse(2,2);
        Utilities::matrixinverse(sInverse, sCovarianceMatrix);
        std::pair<double, double> dRegCoefs;
        double dY = 0.0, dXY = 0.0, dtemp = 0.0;
        for (std::size_t iPath = 0 ; iPath < iNPaths_ ; ++iPath)
        {
            dtemp = dFinalUnderlying[iPath];
            dXY += dtemp * dPayoff[iPath];
            dY += dPayoff[iPath];
        }
        dXY /= iNPaths_;
        dY /= iNPaths_;
        
        dRegCoefs.first     = sInverse(0, 0) * dY + sInverse(0, 1) * dXY;
        dRegCoefs.second    = sInverse(1, 0) * dY + sInverse(1, 1) * dXY;
        
        return dRegCoefs;
    }
    
    std::pair<double, double> PayoffLinearization::Linearise(const Finance::Processes::DiffusionProcess &sDiffusionProcess,
                                                             const Finance::Payoff::Payoff & sPayoff,
                                                             std::vector<double> &dSimulationDates) const
    {
        //  Simulate the stock price
        Utilities::SimulationData sSimulatedData = sDiffusionProcess.simulate(dSimulationDates, iNPaths_, 0);
        
        //  Get the end date distribution of the stock price
        double dEndDate = dSimulationDates.back();
        std::vector<double> dFinalUnderlying = sSimulatedData.Get(dEndDate);
        sSimulatedData.~SimulationData();
        
        //  Get the corresponding Payoff
        std::vector<double> dPayoff(iNPaths_, 0.0);
        
        for (std::size_t iPath = 0 ; iPath < iNPaths_ ; ++iPath)
        {
            dPayoff[iPath] = sPayoff.pay(dFinalUnderlying[iPath]);
        }
        return ComputeRegCoefs(dPayoff, dFinalUnderlying);
    }
}