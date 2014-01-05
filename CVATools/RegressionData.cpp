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
    RegressionData::RegressionData() : iNObservations_(0), iNVars_(0)
    {}
    
    RegressionData::RegressionData(std::size_t iNObservations, std::size_t iNVars) : iNVars_(iNVars), iNObservations_(iNObservations)
    {
        dData_.resize(iNObservations * iNVars);
    }
    
    RegressionData::RegressionData(const std::vector<double> & dData) : dData_(dData), iNVars_(1), iNObservations_(dData.size())
    {}
    
    double& RegressionData::operator ()(int i, int j)
    {
        REQUIREEXCEPTION(i >= 0 && j >= 0, "Indexes are negative");
        REQUIREEXCEPTION(i < iNObservations_, "Observation index is out of bounds");
        REQUIREEXCEPTION(j < iNVars_, "Variable index is out of bounds");
        
        return dData_.at(i + j * iNObservations_);
    }
    
    double& RegressionData::operator ()(int i, int j) const
    {
        REQUIREEXCEPTION(i >= 0 && j >= 0, "Indexes are negative");
        REQUIREEXCEPTION(i < iNObservations_, "Observation index is out of bounds");
        REQUIREEXCEPTION(j < iNVars_, "Variable index is out of bounds");
        
        return (double&)(dData_.at(i + j * iNObservations_));
    }
    
    double& RegressionData::operator ()(size_t i, size_t j)
    {
        REQUIREEXCEPTION(i < iNObservations_, "Observation index is out of bounds");
        REQUIREEXCEPTION(j < iNVars_, "Variable index is out of bounds");
        
        return dData_.at(i + j * iNObservations_);
    }
    
    double& RegressionData::operator ()(size_t i, size_t j) const
    {
        REQUIREEXCEPTION(i < iNObservations_, "Observation index is out of bounds");
        REQUIREEXCEPTION(j < iNVars_, "Variable index is out of bounds");
        
        return (double&)dData_.at(i + j * iNObservations_);
    }
}