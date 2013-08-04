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

namespace Maths
{
    class PayoffLinearization
    {
        std::size_t iNPaths_;
        
    public:
        PayoffLinearization(std::size_t iNPaths);
        
        //  Method that return a pair of double - the two regression coefficients on the constant and on S_t
        std::pair<double, double> Linearise(const Finance::Processes::DiffusionProcess & sDiffusionProcess,
                                            const Finance::Payoff::Payoff & sPayoff,
                                            std::vector<double>& dSimulationDates) const;
    };
}

#endif /* defined(__CVATools__PayoffLinearization__) */
