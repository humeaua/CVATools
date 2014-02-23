//
//  RegressionData.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 27/07/13.
//
//

#ifndef __CVATools__RegressionData__
#define __CVATools__RegressionData__

#include <vector>
#include "Matrix.h"

namespace Utilities
{
    class RegressionData : public Matrix<double>
    {
    public:
        RegressionData();
        RegressionData(std::size_t iNObservations, std::size_t iNVars);
        RegressionData(const std::vector<double> & dData);
        RegressionData(const Utilities::Matrix<double> & data);
        
        //  Getters
        virtual std::size_t GetNbObservations() const;
        virtual std::size_t GetNbVariables() const;
    };
}

#endif /* defined(__CVATools__RegressionData__) */
