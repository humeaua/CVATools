//
//  SimulationData.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 15/03/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "SimulationData.h"

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