
//
//  MargrabeOptionStochasticRates
//  CVATools
//
//  Created by Alexandre HUMEAU on 13/04/13.
//
//

#include "MargrabeOptionStochasticRates.h"

namespace Finance
{
    namespace Option
    {
        MargrabeOptionStochasticRates::MargrabeOptionStochasticRates(double dT,
                                                                     double dK,
                                                                     const Matrix & sCorrelationMatrix,
                                                                     const std::vector<double>& dInitialValues,
                                                                     double dSigma1,
                                                                     double dSigma2)
        :
        PayoffMargrabe(dK),
        dT_(dT),
        DiffusionProcessMultiDim(3, sCorrelationMatrix, dInitialValues),
        dS1_(dInitialValues[0]),
        dS2_(dInitialValues[1]),
        dR0_(dInitialValues[2]),
        dSigma1_(dSigma1),
        dSigma2_(dSigma2)
        {}
        
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
        DiffusionProcessMultiDim(3, Matrix(3, 3), dInitialValues),
        dS1_(dInitialValues[0]),
        dS2_(dInitialValues[1]),
        dR0_(dInitialValues[2]),
        dSigma1_(dSigma1),
        dSigma2_(dSigma2)
        {
            sCorrelationMatrix_.set(1, 2, dRho12);
            sCorrelationMatrix_.set(2, 1, dRho12);
            sCorrelationMatrix_.set(1, 3, dRhor1);
            sCorrelationMatrix_.set(3, 1, dRhor1);
            sCorrelationMatrix_.set(2, 3, dRhor2);
            sCorrelationMatrix_.set(3, 2, dRhor2);
            sCorrelationMatrix_.set(1, 1, 1.0);
            sCorrelationMatrix_.set(2, 2, 1.0);
            sCorrelationMatrix_.set(3, 3, 1.0);
        }
        
        MargrabeOptionStochasticRates::~MargrabeOptionStochasticRates()
        {}
    }
}