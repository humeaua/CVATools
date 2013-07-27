//
//  RegressionMethod.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 27/07/13.
//
//

#ifndef __CVATools__RegressionMethod__
#define __CVATools__RegressionMethod__

#include <iostream>
#include "Vector.h"
#include "RegressionData.h"

namespace Maths
{
    //  Base class for regression
    class RegressionMethod
    {
        virtual std::vector<double> GetPredictedValues(const Utilities::RegressionData & sRegressionData,
                                                       const std::vector<double> & sResponse) const = 0;
        virtual Utilities::MyVector<double> GetPredictedValues(const Utilities::RegressionData & sRegressionData,
                                                               const Utilities::MyVector<double> & sResponse) const = 0;
    
    };
}

#endif /* defined(__CVATools__RegressionMethod__) */
