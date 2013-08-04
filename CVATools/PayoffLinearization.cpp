//
//  PayoffLinearization.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 20/07/13.
//
//

#include "PayoffLinearization.h"
#include "Matrix.h"

namespace Maths
{
    PayoffLinearization::PayoffLinearization(std::size_t iNPaths) : iNPaths_(iNPaths)
    {}
    
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
        
        std::pair<double, double> dRegCoefs;
        double dX = 0, dX2 = 0, dXY = 0, dtemp, dY = 0;
        Utilities::Matrix sCovarMatrix(2,2), sInverse(2,2);
        
        //  Get the corresponding Payoff
        double * dPayoff = new double[iNPaths_];
        if (!dPayoff)
        {
            goto FREE_RETURN;
        }
        
        for (std::size_t iPath = 0 ; iPath < iNPaths_ ; ++iPath)
        {
            dPayoff[iPath] = sPayoff.pay(dFinalUnderlying[iPath]);
        }
        
        for (std::size_t iPath = 0 ; iPath < iNPaths_ ; ++iPath)
        {
            dtemp = dFinalUnderlying[iPath];
            dX += dtemp;
            dX2 += dtemp * dtemp;
            dXY += dtemp * dPayoff[iPath];
            dY += dPayoff[iPath];
        }
        dXY /= iNPaths_;
        dX2 /= iNPaths_;
        dX /= iNPaths_;
        dY /= iNPaths_;
        
        sCovarMatrix.set(0, 0, 1);
        sCovarMatrix.set(0, 1, dX);
        sCovarMatrix.set(1, 0, dX);
        sCovarMatrix.set(1, 1, dX2);
        
        Utilities::matrixinverse(sInverse, sCovarMatrix);
        
        dRegCoefs.first     = sInverse(0, 0) * dY + sInverse(0, 1) * dXY;
        dRegCoefs.second    = sInverse(1, 0) * dY + sInverse(1, 1) * dXY;
        
    FREE_RETURN:
        delete[] dPayoff;
        return dRegCoefs;
    }
}