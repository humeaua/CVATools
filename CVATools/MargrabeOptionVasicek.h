//
//  MargrabeOptionVasicek.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 13/04/13.
//
//

#ifndef CVATools_MargrabeOptionVasicek_h
#define CVATools_MargrabeOptionVasicek_h

#include "MargrabeOptionStochasticRates.h"

/*
 This class describes a Margrabe Option Price simulator
 
 dS^1_t = r_t S^1_t dt + \sigma_1 S^1_t dW^1_t
 dS^2_t = r_t S^2_t dt + \sigma_2 S^2_t dW^2_t
 dr_t = a(b-r_t) dt + \sigma dW^3_t
 
 the goal of the class is to price a Margrabe option of payoff at time T (S_1 - K S_2)_+
 */

namespace Finance
{
    namespace Option
    {
        class MargrabeOptionVasicek : public MargrabeOptionStochasticRates
        {
        protected:
            double dA_, dB_, dSigma_;
        public:
            MargrabeOptionVasicek(double dT, double dK, const Utilities::Matrix<double> & sCorrelationMatrix, const std::vector<double>& dInitialValues, double dA, double dB, double dSigma, double dSigma1, double dSigma2);
            MargrabeOptionVasicek(double dT, double dK, double dRho12, double dRhor1, double dRhor2, const std::vector<double>& dInitialValues, double dA, double dB, double dSigma, double dSigma1, double dSigma2);
            MargrabeOptionVasicek(double dT, double dK, const Utilities::Matrix<double> & sCorrelationMatrix, const std::vector<double>& dInitialValues, double dA, double dB, double dSigma, double dSigma1, double dSigma2, const std::vector<Processes::StochProcessSimulation> & sSimulationParams);
            MargrabeOptionVasicek(double dT, double dK, double dRho12, double dRhor1, double dRhor2, const std::vector<double>& dInitialValues, double dA, double dB, double dSigma, double dSigma1, double dSigma2, const std::vector<Processes::StochProcessSimulation> & sSimulationParams);
            
            //  MultiDimensional Drift drift
            virtual DVector MultiDrift(double dt, DVector dx) const ;
            
            //  MultiDimensional volatility vector
            virtual DVector MultiVol(double dt, DVector dx) const;
            
            virtual double alpha(double t, double r_t) const;
            virtual double beta(double t, double r_t) const;
            
            //  Simulation method
            virtual Utilities::SimulationDataMultiDim simulate(std::vector<double> & dDates, std::size_t iNPaths, long long lSeed) const;
            
        };
    }
}

#endif
