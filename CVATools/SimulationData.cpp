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

namespace Utilities
{
    SimulationData::SimulationData()
    {}
    
    SimulationData::~SimulationData()
    {
        for (std::map<double, std::map<std::size_t, double> >::iterator iter = dData_.begin() ; iter != dData_.end() ; ++iter)
        {
            iter->second.clear();
        }
        dData_.clear();
    }
    
    void SimulationData::Put(double dDate, std::size_t iPath, double dValue)
    {
        if (dData_.count(dDate) != 0)
        {
            if (dData_.find(dDate)->second.count(iPath) != 0)
            {
                dData_.find(dDate)->second.find(iPath)->second = dValue;
            }
            else
            {
                dData_.find(dDate)->second[iPath] = dValue;
            }
        }
        else
        {
            dData_[dDate][iPath] = dValue;
        }
    }
    
    std::map<double, std::map<std::size_t, double> > SimulationData::GetData() const
    {
        return dData_;
    }
    
    double SimulationData::Get(double dDate, std::size_t iPath) const
    {
        if (dData_.count(dDate) != 0)
        {
            if (dData_.find(dDate)->second.count(iPath) != 0)
            {
                return dData_.find(dDate)->second.find(iPath)->second;
            }
            else
            {
                throw Utilities::MyException("SimulationData::Get : Path not found");
            }
        }
        else
        {
            throw Utilities::MyException("SimulationData::Get : Date not found");
        }
    }
    
    std::vector<double> SimulationData::Get(double dDate) const
    {
        if (dData_.count(dDate))
        {
            std::vector<double> dResult;
            std::map<std::size_t, double> mMyMap = dData_.find(dDate)->second;
            for (std::map<std::size_t, double>::iterator it = mMyMap.begin() ; it != mMyMap.end() ; ++it)
            {
                dResult.push_back(it->second);
            }
            return dResult;
        }
        else
        {
            throw Utilities::MyException("SimulationData::Get : Date not found");
        }
    }

    void SimulationData::Apply(double (*func)(double))
    {
        std::map<double, std::map<std::size_t, double> >::iterator itDates = dData_.begin();
        for ( ; itDates != dData_.end() ; ++itDates)
        {
            std::map<std::size_t, double>::iterator itPaths = itDates->second.begin();
            for ( ; itPaths != itDates->second.end() ; ++itPaths)
            {
                itPaths->second = func(itPaths->second);
            }
        }
    }
}