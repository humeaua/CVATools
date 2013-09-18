//
//  RegressionMethod.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 27/07/13.
//
//

#include "RegressionMethod.h"

namespace Maths
{
    double RegressionMethod::R2(const Utilities::MyVector<double> &sResponse, const Utilities::MyVector<double> &sPredictedValues) const
    {
        Utilities::MyVector<double> result(sResponse.size(), 0.0);
        std::transform(sResponse.begin(), sResponse.end(), sPredictedValues.begin(), std::back_inserter(result), std::minus<double>());
        
        return 1 - std::inner_product(result.begin(), result.end(), result.begin(), 0.0) /  std::inner_product(sResponse.begin(), sResponse.end(), result.begin(), 0.0);
    }
    
    double RegressionMethod::R2FromScratch(const Utilities::RegressionData &sRegressionData, const Utilities::MyVector<double> &sResponse) const
    {
        return R2(sResponse, GetPredictedValues(sRegressionData, sResponse));
    }
}