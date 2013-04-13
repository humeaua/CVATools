
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
                                                             const std::vector<double>& dInitialValues)
:
PayoffMargrabe(dK),
dT_(dT),
DiffusionProcessMultiDim(3, sCorrelationMatrix, dInitialValues)
{}

MargrabeOptionStochasticRates::~MargrabeOptionStochasticRates()
{}