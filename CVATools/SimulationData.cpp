//
//  SimulationData.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 15/03/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "SimulationData.h"
#include "Exception.h"
#include "VectorUtilities.h"

namespace Utilities
{
    SimulationData::SimulationData(std::size_t iNPaths, std::size_t iNDates) : RegressionData(iNPaths, iNDates)
    {}
    
    SimulationData::SimulationData(const std::vector<std::vector<double> > & dData, const std::vector<double>& dDates) : RegressionData(dData.size(), dDates.size()), dDates_(dDates)
    {
        for (std::size_t iPath = 0 ; iPath < dData.size() ; ++iPath)
        {
            for (std::size_t iDate = 0 ; iDate < dDates_.size() ; ++iDate)
            {
                (*this)(iPath, iDate) = dData.at(iPath).at(iPath);
            }
        }
    }
    
    SimulationData::~SimulationData()
    {}
    
    void SimulationData::AddDate(double dDate)
    {
        dDates_.push_back(dDate);
    }
    
    double& SimulationData::operator ()(size_t i, size_t j)
    {
        REQUIREEXCEPTION(i < iNObservations_, "Observation index is out of bounds");
        REQUIREEXCEPTION(j < iNVars_, "Variable index is out of bounds");
        
        return dData_.at(i + j * iNObservations_);
    }
    
    double& SimulationData::operator ()(size_t i, size_t j) const
    {
        REQUIREEXCEPTION(i < iNObservations_, "Observation index is out of bounds");
        REQUIREEXCEPTION(j < iNVars_, "Variable index is out of bounds");
        
        return (double&)dData_.at(i + j * iNObservations_);
    }
    
    std::vector<double> SimulationData::Get(double dDate) const
    {
        std::size_t iIndex = Utilities::GetIndex(dDates_, dDate);
        REQUIREEXCEPTION(iIndex != -1, "Date not found");
        
        return Subset(dData_, iIndex * iNObservations_, (iIndex + 1) * iNObservations_ - 1);
    }
    
    std::map<double, std::map<std::size_t, double> > SimulationData::GetData() const
    {
        std::map<double, std::map<std::size_t, double> > mResult;
        for (std::size_t iDate = 0 ; iDate < dDates_.size() ; ++iDate)
        {
            std::map<std::size_t, double> dLocalMap;
            for (std::size_t iPath = 0 ; iPath < iNObservations_ ; ++iPath)
            {
                dLocalMap[iPath] = (*this)(iPath, iDate);
            }
            mResult[dDates_.at(iDate)] = dLocalMap;
        }
        return mResult;
    }
}