//
//  LeastSquareRegression.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 27/07/13.
//
//

#ifndef __CVATools__LeastSquareRegression__
#define __CVATools__LeastSquareRegression__

#include <iostream>
#include "Matrix.h"
#include "RegressionMethod.h"

namespace Maths {
    
    //  Base class for least square regression
    class LeastSquareRegression : public RegressionMethod
    {
    public:
        virtual Utilities::Matrix<double> ComputeCovarianceMatrix(const Utilities::RegressionData & sRegressionData) const = 0;
    
        virtual Utilities::MyVector<double> ComputeRegCoefs(const Utilities::RegressionData & sRegressionData,
                                                            const Utilities::MyVector<double> & sResponse) const;
        virtual std::vector<double> ComputeRegCoefs(const Utilities::RegressionData & sRegressionData,
                                                    const std::vector<double> & sResponse) const;
        
        //  Methods from Base Class RegressionMethod in both std::vector and Utilites::MyVector
        virtual std::vector<double> GetPredictedValues(const Utilities::RegressionData & sRegressionData,
                                                       const std::vector<double> & sResponse) const;
        virtual Utilities::MyVector<double> GetPredictedValues(const Utilities::RegressionData & sRegressionData,
                                                               const Utilities::MyVector<double> & sResponse) const;
        
    };
}

#endif /* defined(__CVATools__LeastSquareRegression__) */
