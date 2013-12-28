
//
//  MargrabeOptionStochasticRates
//  CVATools
//
//  Created by Alexandre HUMEAU on 13/04/13.
//
//

#include "MargrabeOptionStochasticRates.h"
#include "Require.h"

namespace Finance
{
    namespace Option
    {
        MargrabeOptionStochasticRates::MargrabeOptionStochasticRates(double dT,
                                                                     double dK,
                                                                     const Utilities::Matrix<double> & sCorrelationMatrix,
                                                                     const std::vector<double>& dInitialValues,
                                                                     double dSigma1,
                                                                     double dSigma2)
        :
        PayoffMargrabe(dK),
        dT_(dT),
        DiffusionProcessMultiDim(3, sCorrelationMatrix, dInitialValues, std::vector<Processes::StochProcessSimulation>(3, Processes::StochProcessSimulation())),
        dS1_(dInitialValues.at(0)),
        dS2_(dInitialValues.at(1)),
        dR0_(dInitialValues.at(2)),
        dSigma1_(dSigma1),
        dSigma2_(dSigma2)
        {
            Processes::StochProcessSimulation sFloored, sNonFloored;
            sFloored.SetFloor(0.0, true);
            sSimulationParams_.resize(3);
            sSimulationParams_.at(0) = sFloored; // S1
            sSimulationParams_.at(1) = sFloored; // S2
            sSimulationParams_.at(2) = sNonFloored; // r
        }
        
        MargrabeOptionStochasticRates::MargrabeOptionStochasticRates(double dT,
                                                                     double dK,
                                                                     double dRho12,
                                                                     double dRhor1,
                                                                     double dRhor2,
                                                                     const std::vector<double>& dInitialValues,
                                                                     double dSigma1,
                                                                     double dSigma2)
        :
        PayoffMargrabe(dK),
        dT_(dT),
        DiffusionProcessMultiDim(3, Utilities::Matrix<double>(3, 3), dInitialValues, std::vector<Processes::StochProcessSimulation>(3, Processes::StochProcessSimulation())),
        dS1_(dInitialValues.at(0)),
        dS2_(dInitialValues.at(1)),
        dR0_(dInitialValues.at(2)),
        dSigma1_(dSigma1),
        dSigma2_(dSigma2)
        {
            sCorrelationMatrix_(1, 2) = dRho12;
            sCorrelationMatrix_(2, 1) = dRho12;
            sCorrelationMatrix_(1, 3) = dRhor1;
            sCorrelationMatrix_(3, 1) = dRhor1;
            sCorrelationMatrix_(2, 3) = dRhor2;
            sCorrelationMatrix_(3, 2) = dRhor2;
            sCorrelationMatrix_(1, 1) = 1.0;
            sCorrelationMatrix_(2, 2) = 1.0;
            sCorrelationMatrix_(3, 3) = 1.0;
            
            Processes::StochProcessSimulation sFloored, sNonFloored;
            sFloored.SetFloor(0.0, true);
            
            sSimulationParams_.at(0) = sFloored; // S1
            sSimulationParams_.at(1) = sFloored; // S2
            sSimulationParams_.at(2) = sNonFloored; // r
        }
        
        MargrabeOptionStochasticRates::MargrabeOptionStochasticRates(double dT, double dK, const Utilities::Matrix<double> & sCorrelationMatrix, const std::vector<double>& dInitialValues, double dSigma1, double dSigma2, const std::vector<Processes::StochProcessSimulation> & sSimulationParams)
        :
        PayoffMargrabe(dK),
        dT_(dT),
        DiffusionProcessMultiDim(3, sCorrelationMatrix, dInitialValues, sSimulationParams),
        dS1_(dInitialValues.at(0)),
        dS2_(dInitialValues.at(1)),
        dR0_(dInitialValues.at(2)),
        dSigma1_(dSigma1),
        dSigma2_(dSigma2)
        {
            Utilities::requireException(sSimulationParams.size() == 3, "Size of simulation parameters has to be 3", "MargrabeOptionStochasticRates::MargrabeOptionStochasticRates");
        }
        
        MargrabeOptionStochasticRates::MargrabeOptionStochasticRates(double dT, double dK, double dRho12, double dRhor1, double dRhor2, const std::vector<double>& dInitialValues, double dSigma1, double dSigma2, const std::vector<Processes::StochProcessSimulation> & sSimulationParams)
        :
        PayoffMargrabe(dK),
        dT_(dT),
        DiffusionProcessMultiDim(3, Utilities::Matrix<double>(3, 3), dInitialValues, sSimulationParams),
        dS1_(dInitialValues.at(0)),
        dS2_(dInitialValues.at(1)),
        dR0_(dInitialValues.at(2)),
        dSigma1_(dSigma1),
        dSigma2_(dSigma2)
        {
            Utilities::requireException(sSimulationParams.size() == 3, "Size of simulation parameters has to be 3", "MargrabeOptionStochasticRates::MargrabeOptionStochasticRates");
            sCorrelationMatrix_(1, 2) = dRho12;
            sCorrelationMatrix_(2, 1) = dRho12;
            sCorrelationMatrix_(1, 3) = dRhor1;
            sCorrelationMatrix_(3, 1) = dRhor1;
            sCorrelationMatrix_(2, 3) = dRhor2;
            sCorrelationMatrix_(3, 2) = dRhor2;
            sCorrelationMatrix_(1, 1) = 1.0;
            sCorrelationMatrix_(2, 2) = 1.0;
            sCorrelationMatrix_(3, 3) = 1.0;
        }
    }
}