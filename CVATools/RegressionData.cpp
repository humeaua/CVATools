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
        dData_.resize(iNObservations);
        for (std::size_t i = 0 ; i < iNObservations ; ++i)
        {
            dData_[i].resize(iNVars);
        }
    }
    
    RegressionData::RegressionData(const std::vector<std::vector<double> > & dData) : dData_(dData)
    {
        iNObservations_ = dData.size();
        if (iNObservations_ > 0)
        {
            iNVars_ = dData.front().size();
        }
        else
        {
            iNVars_ = 0;
        }
    }
    
    double RegressionData::operator ()(int i, int j)
    {
        requireException(i >= 0 && j >= 0, "Indexes are negative", "RegressionData::operator (int,int)");
        requireException(i < iNObservations_, "Observation index is out of bounds", "RegressionData::operator (int,int)");
        requireException(j < iNVars_, "Variable index is out of bounds", "RegressionData::operator (int,int)");
        
        return dData_[i][j];
    }
    
    double RegressionData::operator ()(int i, int j) const
    {
        requireException(i >= 0 && j >= 0, "Indexes are negative", "RegressionData::operator (int,int)");
        requireException(i < iNObservations_, "Observation index is out of bounds", "RegressionData::operator (int,int)");
        requireException(j < iNVars_, "Variable index is out of bounds", "RegressionData::operator (int,int)");
        
        return dData_[i][j];
    }
    
    double RegressionData::operator ()(size_t i, size_t j)
    {
        requireException(i < iNObservations_, "Observation index is out of bounds", "RegressionData::operator (int,int)");
        requireException(j < iNVars_, "Variable index is out of bounds", "RegressionData::operator (int,int)");
        
        return dData_[i][j];
    }
    
    double RegressionData::operator ()(size_t i, size_t j) const
    {
        requireException(i < iNObservations_, "Observation index is out of bounds", "RegressionData::operator (int,int)");
        requireException(j < iNVars_, "Variable index is out of bounds", "RegressionData::operator (int,int)");
        
        return dData_[i][j];
    }
}