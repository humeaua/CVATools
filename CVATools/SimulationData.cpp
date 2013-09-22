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
    
    SimulationData::~SimulationData()
    {
        dDates_.clear();
    }
    
    void SimulationData::AddDate(double dDate)
    {
        dDates_.push_back(dDate);
    }
    
    double& SimulationData::operator ()(size_t i, size_t j)
    {
        requireException(i < iNObservations_, "Observation index is out of bounds", "SimulationData::operator (size_t,size_t)");
        requireException(j < iNVars_, "Variable index is out of bounds", "SimulationData::operator (size_t,size_t)");
        
        return dData_[i + j * iNObservations_];
    }
    
    double& SimulationData::operator ()(size_t i, size_t j) const
    {
        requireException(i < iNObservations_, "Observation index is out of bounds", "SimulationData::operator (size_t,size_t)");
        requireException(j < iNVars_, "Variable index is out of bounds", "SimulationData::operator (size_t,size_t)");
        
        return (double&)dData_[i + j * iNObservations_];
    }
    
    std::vector<double> SimulationData::Get(double dDate) const
    {
        std::size_t iIndex = Utilities::GetIndex(dDates_, dDate);
        requireException(iIndex != -1, "Date not found", "SimulationData::Get(double dDate)");
        
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
            mResult[dDates_[iDate]] = dLocalMap;
        }
        return mResult;
    }
}