//
//  PayoffLinearization.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 20/07/13.
//
//

#ifndef __CVATools__PayoffLinearization__
#define __CVATools__PayoffLinearization__

#include <iostream>
#include "Payoff.h"
#include "DiffusionProcess.h"
#include "Matrix.h"
#include "LinearRegression.h"

namespace Maths
{
    class PayoffLinearization : public LinearRegression
    {
        std::size_t iNPaths_;
        
        virtual Utilities::Matrix ComputeCovarianceMatrix(const std::vector<double> & dFinalUnderlying) const;
        virtual std::pair<double, double> ComputeRegCoefs(const std::vector<double> & dPayoff,
                                                          const std::vector<double> & dFinalUnderlying) const;
    public:
        PayoffLinearization(std::size_t iNPaths);
        
        //  Method that return a pair of double - the two regression coefficients on the constant and on S_t
        virtual std::pair<double, double> Linearise(const Finance::Processes::DiffusionProcess & sDiffusionProcess,
                                                    const Finance::Payoff::Payoff & sPayoff,
                                                    std::vector<double>& dSimulationDates) const;
    };
}

#endif /* defined(__CVATools__PayoffLinearization__) */
