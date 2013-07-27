//
//  LinearRegression.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 27/07/13.
//
//

#ifndef __CVATools__LinearRegression__
#define __CVATools__LinearRegression__

#include <iostream>
#include "LeastSquareRegression.h"

namespace Maths
{
    class LinearRegression: public LeastSquareRegression
    {
    protected:
        bool bAddConstantInRegression_;
    public:
        LinearRegression(bool bAddConstantInRegression);
        virtual Utilities::Matrix ComputeCovarianceMatrix(const Utilities::RegressionData & sRegressionData) const;
        
    };
}
#endif /* defined(__CVATools__LinearRegression__) */
