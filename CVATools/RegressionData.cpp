//
//  RegressionData.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 27/07/13.
//
//

#include "RegressionData.h"
#include "Require.h"

namespace Utilities
{
    RegressionData::RegressionData() : Matrix<double>(0,0)
    {}
    
    RegressionData::RegressionData(std::size_t iNObservations, std::size_t iNVars) : Matrix<double>(iNObservations, iNVars)
    {}
    
    RegressionData::RegressionData(const std::vector<double> & dData) : Matrix<double>(dData.size(), (std::size_t)1)
    {
        std::size_t zero = 0;
        for (std::size_t i = 0 ; i < dData.size() ; ++i)
        {
            (*this)(i,zero) = dData.at(i);
        }
    }
    
    RegressionData::RegressionData(const Matrix<double> & data) : Matrix<double>(data)
    {}
    
    //  Getters
    std::size_t RegressionData::GetNbObservations() const
    {
        return static_cast<std::size_t>(getrows());
    }
    std::size_t RegressionData::GetNbVariables() const
    {
        return static_cast<std::size_t>(getcols());
    }
}