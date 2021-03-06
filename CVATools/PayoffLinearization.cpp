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
    PayoffLinearization::PayoffLinearization(std::size_t iNPaths) : iNPaths_(iNPaths), Maths::LinearRegression(true)
    {}
    
    Utilities::Matrix<double> PayoffLinearization::ComputeCovarianceMatrix(const std::vector<double> & dFinalUnderlying) const
    {
        Utilities::Matrix<double> sCovarMatrix(2,2);
        double dtemp = 0.0, dX = 0.0, dX2 = 0.0;
        for (std::size_t iPath = 0 ; iPath < iNPaths_ ; ++iPath)
        {
            dtemp = dFinalUnderlying.at(iPath);
            dX += dtemp;
            dX2 += dtemp * dtemp;
        }
        dX /= iNPaths_;
        dX2 /= iNPaths_;
        
        sCovarMatrix(0,0) = 1.0;
        sCovarMatrix(0,1) = sCovarMatrix(1, 0) = dX;
        sCovarMatrix(1,1) = dX2;
        
        return sCovarMatrix;
    }
    
    std::pair<double, double> PayoffLinearization::ComputeRegCoefs(const std::vector<double> & dPayoff,
                                                                   const std::vector<double> & dFinalUnderlying) const
    {
        Utilities::Matrix<double> sCovarianceMatrix = ComputeCovarianceMatrix(dFinalUnderlying), sInverse(2,2);
        Utilities::matrixinverse(sInverse, sCovarianceMatrix);
        std::pair<double, double> dRegCoefs;
        double dY = 0.0, dXY = 0.0, dtemp = 0.0;
        for (std::size_t iPath = 0 ; iPath < iNPaths_ ; ++iPath)
        {
            dtemp = dFinalUnderlying.at(iPath);
            dXY += dtemp * dPayoff.at(iPath);
            dY += dPayoff.at(iPath);
        }
        dXY /= iNPaths_;
        dY /= iNPaths_;
        
        dRegCoefs.first     = sInverse(0, 0) * dY + sInverse(0, 1) * dXY;
        dRegCoefs.second    = sInverse(1, 0) * dY + sInverse(1, 1) * dXY;
        
        return dRegCoefs;
    }
    
    std::pair<double, double> PayoffLinearization::Linearise(const Finance::Processes::DiffusionProcess &sDiffusionProcess,
                                                             const Finance::Payoff::BasePayoff1D & sPayoff,
                                                             std::vector<double> &dSimulationDates) const
    {
        //  Simulate the stock price
        Utilities::SimulationData sSimulatedData = sDiffusionProcess.simulate(dSimulationDates, iNPaths_);
        
        std::vector<double> dPayoff(iNPaths_, 0.0);
        
        std::vector<double> dFinalUnderlying = sSimulatedData.Get(dSimulationDates.back());
        Utilities::RegressionData sRegressionData = dFinalUnderlying;
        
        for (std::size_t iPath = 0 ; iPath < iNPaths_ ; ++iPath)
        {
            dPayoff.at(iPath) = sPayoff(dFinalUnderlying.at(iPath));
        }
        
        std::vector<double> bla = LeastSquareRegression::ComputeRegCoefs(sRegressionData, dPayoff);
        
        return std::make_pair(bla.front(), bla.back());
    }
}