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
        MargrabeOptionVasicek::MargrabeOptionVasicek(double dT,
                                                     double dK,
                                                     const Utilities::Matrix<double> & sCorrelationMatrix,
                                                     const std::vector<double>& dInitialValues,
                                                     double dA,
                                                     double dB,
                                                     double dSigma,
                                                     double dSigma1,
                                                     double dSigma2,
                                                     long long & lSeed)
        :
        MargrabeOptionStochasticRates(dT, dK, sCorrelationMatrix, dInitialValues, dSigma1, dSigma2, lSeed),
        dA_(dA),
        dB_(dB),
        dSigma_(dSigma)
        {}
        
        MargrabeOptionVasicek::MargrabeOptionVasicek(double dT,
                                                     double dK,
                                                     double dRho12,
                                                     double dRhor1,
                                                     double dRhor2,
                                                     const std::vector<double>& dInitialValues,
                                                     double dA,
                                                     double dB,
                                                     double dSigma,
                                                     double dSigma1,
                                                     double dSigma2,
                                                     long long & lSeed)
        :
        MargrabeOptionStochasticRates(dT, dK, dRho12, dRhor1, dRhor2, dInitialValues, dSigma1, dSigma2, lSeed),
        dA_(dA),
        dB_(dB),
        dSigma_(dSigma)
        {}
        
        MargrabeOptionVasicek::MargrabeOptionVasicek(double dT,
                                                     double dK,
                                                     const Utilities::Matrix<double> & sCorrelationMatrix,
                                                     const std::vector<double>& dInitialValues,
                                                     double dA,
                                                     double dB,
                                                     double dSigma,
                                                     double dSigma1,
                                                     double dSigma2,
                                                     const std::vector<Processes::StochProcessSimulation> & sSimulationParams,
                                                     long long & lSeed)
        :
        MargrabeOptionStochasticRates(dT, dK, sCorrelationMatrix, dInitialValues, dSigma1, dSigma2, sSimulationParams, lSeed),
        dA_(dA),
        dB_(dB),
        dSigma_(dSigma)
        {}
        
        MargrabeOptionVasicek::MargrabeOptionVasicek(double dT,
                                                     double dK,
                                                     double dRho12,
                                                     double dRhor1,
                                                     double dRhor2,
                                                     const std::vector<double>& dInitialValues,
                                                     double dA,
                                                     double dB,
                                                     double dSigma,
                                                     double dSigma1,
                                                     double dSigma2,
                                                     const std::vector<Processes::StochProcessSimulation> & sSimulationParams,
                                                     long long & lSeed)
        :
        MargrabeOptionStochasticRates(dT, dK, dRho12, dRhor1, dRhor2, dInitialValues, dSigma1, dSigma2, sSimulationParams, lSeed),
        dA_(dA),
        dB_(dB),
        dSigma_(dSigma)
        {}
        
        std::vector<double> MargrabeOptionVasicek::MultiDrift(double dt, std::vector<double> dx) const
        {
            return std::vector<double>(3, 0.0);
        }
        
        //  MultiDimensional Variance --> not used but must be declared
        std::vector<double> MargrabeOptionVasicek::MultiVol(double dt, std::vector<double> dx) const
        {
            return std::vector<double>(3, 0.0);
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
        Utilities::SimulationDataMultiDim MargrabeOptionVasicek::simulate(std::vector<double> & dDates, std::size_t iNPaths) const
        {
            //  we need to store the two asset prices, the integral of the short rate and the short rate itself
            Utilities::SimulationDataMultiDim sResult(dDates, iNPaths, 4);
            
            //  Set random number simulator engine
            std::tr1::normal_distribution<double> dist(0.0,1.0);
            
            //   store values for initial time step
            std::vector<double> dCurrentValues(4,0.0);
            for (std::size_t iPath = 0 ; iPath < iNPaths ; ++iPath)
            {
                dCurrentValues.at(0) = dS1_;
                dCurrentValues.at(1) = dS2_;
                dCurrentValues.at(2) = 0.0;
                dCurrentValues.at(3) = dR0_;
                sResult.Put(dDates.at(0), iPath, dCurrentValues);
            }
            
            // Choleski Decomposition of correlation matrix
            Utilities::Matrix<double> sCholDec(3,3);
            CholeskiDecomposition(sCorrelationMatrix_, sCholDec);
            std::vector<double> dRandomNumbers(3,0.0), dCorrelatedRN(3,0.0);
            for (std::size_t iPath = 0 ; iPath < iNPaths ; ++iPath)
            {
                double dOldStock1 = dS1_, dOldStock2 = dS2_, dOldIntShortRate = 0.0, dOldShortRate = dR0_, dNewStock1 = 0.0, dNewStock2 = 0.0, dNewIntShortRate = 0.0, dNewShortRate = 0.0;
                for (std::size_t iDate = 1 ; iDate < dDates.size() ; ++iDate)
                {
                    double dt = dDates[iDate] - dDates[iDate - 1];
                    for (std::size_t i = 0 ; i < 3 ; ++i)
                    {
                        dRandomNumbers.at(i) = dist(*m_eng);
                    }
                    mult(dCorrelatedRN, sCholDec, dRandomNumbers);
                    
                    dNewShortRate = dOldShortRate * exp(-dA_ * dt) + dB_ * (1.0 - exp(-dA_ * dt)) + dCorrelatedRN.at(2) * dSigma_ * sqrt((1 - exp(-dA_ * 2.0 * dt)) * 0.5 / dA_);
                    dNewIntShortRate = dOldIntShortRate + dOldShortRate * (1 - exp(-dA_ * dt)) / dA_ + dB_ * (dt - (1 - exp(-dA_ * dt))/ dA_) +  dCorrelatedRN.at(2) * dSigma_ / dA_ * sqrt(dt - 2 * (1 - exp(-dA_ * dt)) / dA_ + (1 - exp(-2. * dA_ * dt)) * 0.5 / dA_);
                    dNewStock1 = dOldStock1 + dNewIntShortRate - dOldIntShortRate - 0.5 * dSigma1_ * dSigma1_ * dt + dSigma1_ * sqrt(dt) * dCorrelatedRN.at(0);
                    dNewStock2 = dOldStock2 + dNewIntShortRate - dOldIntShortRate - 0.5 * dSigma2_ * dSigma2_ * dt + dSigma2_ * sqrt(dt) * dCorrelatedRN.at(1);
                    
                    dCurrentValues.at(0) = dNewStock1;
                    dCurrentValues.at(1) = dNewStock2;
                    dCurrentValues.at(2) = dNewIntShortRate;
                    dCurrentValues.at(3) = dNewShortRate;
                    
                    sResult.Put(dDates.at(iDate), iPath, dCurrentValues);
                    
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