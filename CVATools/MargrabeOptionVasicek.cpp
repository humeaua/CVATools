//
//  MargrabeOptionVasicek.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 13/04/13.
//
//

#include "MargrabeOptionVasicek.h"
#include <tr1/random>

namespace Finance
{
    namespace Option
    {
        MargrabeOptionVasicek::MargrabeOptionVasicek(double dT, double dK, const Utilities::Matrix & sCorrelationMatrix, const std::vector<double>& dInitialValues, double dA, double dB, double dSigma, double dSigma1, double dSigma2) : MargrabeOptionStochasticRates(dT, dK, sCorrelationMatrix, dInitialValues, dSigma1, dSigma2), dA_(dA), dB_(dB), dSigma_(dSigma)
        {}
        
        MargrabeOptionVasicek::MargrabeOptionVasicek(double dT, double dK, double dRho12, double dRhor1, double dRhor2, const std::vector<double>& dInitialValues, double dA, double dB, double dSigma, double dSigma1, double dSigma2) : MargrabeOptionStochasticRates(dT, dK, dRho12, dRhor1, dRhor2, dInitialValues, dSigma1, dSigma2), dA_(dA), dB_(dB), dSigma_(dSigma)
        {}
        
        MargrabeOptionVasicek::~MargrabeOptionVasicek()
        {}
        
        DVector MargrabeOptionVasicek::MultiDrift(double dt, DVector dx) const
        {
            DVector dResult(3);
            return dResult;
        }
        
        //  MultiDimensional Variance --> not used but must be declared
        DVector MargrabeOptionVasicek::MultiVol(double dt, DVector dx) const
        {
            DVector sResult(3);
            return sResult;
        }
        
        double MargrabeOptionVasicek::alpha(double t, double r_t) const
        {
            return dA_ * (dB_ - r_t);
        }
        
        double MargrabeOptionVasicek::beta(double t, double r_t) const
        {
            return dSigma_;
        }
        
        //  Simulation method
        Utilities::SimulationDataMultiDim MargrabeOptionVasicek::simulate(std::vector<double> & dDates, std::size_t iNPaths, long long lSeed) const
        {
            //  we need to store the two asset prices, the integral of the short rate and the short rate itself
            Utilities::SimulationDataMultiDim sResult(dDates, iNPaths, 4);
            
            //  Set random number simulator engine
            std::tr1::ranlux64_base_01 eng; // core engine class
            eng.seed(lSeed);
            std::tr1::normal_distribution<double> dist(0.0,1.0);
            
            //   store values for initial time step
            DVector dCurrentValues(4,0.0);
            for (std::size_t iPath = 0 ; iPath < iNPaths ; ++iPath)
            {
                dCurrentValues[0] = dS1_;
                dCurrentValues[1] = dS2_;
                dCurrentValues[2] = 0.0;
                dCurrentValues[3] = dR0_;
                sResult.Put(dDates[0], iPath, dCurrentValues);
            }
            
            // Choleski Decomposition of correlation matrix
            Utilities::Matrix sCholDec(3,3);
            CholeskiDecomposition(sCorrelationMatrix_, sCholDec);
            DVector dRandomNumbers(3,0.0), dCorrelatedRN(3,0.0);
            for (std::size_t iPath = 0 ; iPath < iNPaths ; ++iPath)
            {
                double dOldStock1 = dS1_, dOldStock2 = dS2_, dOldIntShortRate = 0.0, dOldShortRate = dR0_, dNewStock1 = 0.0, dNewStock2 = 0.0, dNewIntShortRate = 0.0, dNewShortRate = 0.0;
                for (std::size_t iDate = 1 ; iDate < dDates.size() ; ++iDate)
                {
                    double dt = dDates[iDate] - dDates[iDate - 1];
                    for (std::size_t i = 0 ; i < 3 ; ++i)
                    {
                        dRandomNumbers[i] = dist(eng);
                    }
                    mult(dCorrelatedRN, sCholDec, dRandomNumbers);
                    
                    dNewShortRate = dOldShortRate * exp(-dA_ * dt) + dB_ * (1.0 - exp(-dA_ * dt)) + dCorrelatedRN[2] * dSigma_ * sqrt((1 - exp(-dA_ * 2.0 * dt)) * 0.5 / dA_);
                    dNewIntShortRate = dOldIntShortRate + dOldShortRate * (1 - exp(-dA_ * dt)) / dA_ + dB_ * (dt - (1 - exp(-dA_ * dt))/ dA_) +  dCorrelatedRN[2] * dSigma_ / dA_ * sqrt(dt - 2 * (1 - exp(-dA_ * dt)) / dA_ + (1 - exp(-2. * dA_ * dt)) * 0.5 / dA_);
                    dNewStock1 = dOldStock1 + dNewIntShortRate - dOldIntShortRate - 0.5 * dSigma1_ * dSigma1_ * dt + dSigma1_ * sqrt(dt) * dCorrelatedRN[0];
                    dNewStock2 = dOldStock2 + dNewIntShortRate - dOldIntShortRate - 0.5 * dSigma2_ * dSigma2_ * dt + dSigma2_ * sqrt(dt) * dCorrelatedRN[1];
                    
                    dCurrentValues[0] = dNewStock1;
                    dCurrentValues[1] = dNewStock2;
                    dCurrentValues[2] = dNewIntShortRate;
                    dCurrentValues[3] = dNewShortRate;
                    
                    sResult.Put(dDates[iDate], iPath, dCurrentValues);
                    
                    //  update values
                    dOldStock1 = dNewStock1;
                    dOldStock2 = dNewStock2;
                    dOldIntShortRate = dNewIntShortRate;
                    dOldShortRate = dNewShortRate;
                }
            }
            return sResult;
        }
    }
}