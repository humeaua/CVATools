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
                (*this)(iPath, iDate) = dData.at(iPath).at(iDate);
            }
        }
    }
    
    SimulationData::~SimulationData()
    {}
    
    void SimulationData::AddDate(double dDate)
    {
        dDates_.push_back(dDate);
    }
    
    std::vector<double> SimulationData::Get(double dDate) const
    {
        std::size_t iIndex = Utilities::GetIndex(dDates_, dDate);
        REQUIREEXCEPTION(iIndex != -1, "Date not found");
        
        return Subset(m_data, iIndex * GetNbObservations(), (iIndex + 1) * GetNbObservations() - 1);
    }
    
    std::map<double, std::map<std::size_t, double> > SimulationData::GetData() const
    {
        std::map<double, std::map<std::size_t, double> > mResult;
        for (std::size_t iDate = 0 ; iDate < dDates_.size() ; ++iDate)
        {
            std::map<std::size_t, double> dLocalMap;
            for (std::size_t iPath = 0 ; iPath < GetNbObservations() ; ++iPath)
            {
                dLocalMap[iPath] = (*this)(iPath, iDate);
            }
            mResult[dDates_.at(iDate)] = dLocalMap;
        }
        return mResult;
    }
}