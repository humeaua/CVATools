//
//  MargrabeOptionStochasticRates.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 13/04/13.
//
//

#ifndef CVATools_MargrabeOptionStochasticRates_h
#define CVATools_MargrabeOptionStochasticRates_h

#include "PayoffMargrabe.h"
#include "DiffusionProcessMultiDim.h"
#include "DiffusionProcess.h"

/*
 This class describes a Margrabe Option Price simulator
 
 dS^1_t = r_t S^1_t dt + \sigma_1 S^1_t dW^1_t
 dS^2_t = r_t S^2_t dt + \sigma_2 S^2_t dW^2_t
 dr_t = \alpha(t,r_t) dt + \beta(t,r_t) dW^3_t
 
 the goal of the class is to price a Margrabe option of payoff at time T (S_1 - K S_2)_+
 */

namespace Finance
{
    namespace Option
    {
        class MargrabeOptionStochasticRates : public Payoff::PayoffMargrabe, public Finance::Processes::DiffusionProcessMultiDim
        {
        protected:
            double dT_;
            double dS1_, dS2_;
            double dR0_;
            
            double dSigma1_, dSigma2_;
        public:
            MargrabeOptionStochasticRates(double dT, double dK, const Utilities::Matrix<double> & sCorrelationMatrix, const std::vector<double>& dInitialValues, double dSigma1, double dSigma2);
            MargrabeOptionStochasticRates(double dT, double dK, double dRho12, double dRhor1, double dRhor2, const std::vector<double>& dInitialValues, double dSigma1, double dSigma2);
            MargrabeOptionStochasticRates(double dT, double dK, const Utilities::Matrix<double> & sCorrelationMatrix, const std::vector<double>& dInitialValues, double dSigma1, double dSigma2, const std::vector<Processes::StochProcessSimulation> & sSimulationParams);
            MargrabeOptionStochasticRates(double dT, double dK, double dRho12, double dRhor1, double dRhor2, const std::vector<double>& dInitialValues, double dSigma1, double dSigma2, const std::vector<Processes::StochProcessSimulation> & sSimulationParams);
            
            virtual double alpha(double t, double r_t) const = 0;
            virtual double beta(double t, double r_t) const = 0;
        };
    }
}

#endif
