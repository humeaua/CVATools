
//
//  MargrabeOptionStochasticRates
//  CVATools
//
//  Created by Alexandre HUMEAU on 13/04/13.
//
//

#include "MargrabeOptionStochasticRates.h"

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

MargrabeOptionStochasticRates::~MargrabeOptionStochasticRates()
{}