//
//  SimulationDataMultiDim.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 28/03/13.
//
//

#include "SimulationDataMultiDim.h"

//Default constructor
SimulationDataMultiDim::SimulationDataMultiDim()
{}

//  Destructor
SimulationDataMultiDim::~SimulationDataMultiDim()
{}

//  Put function
void SimulationDataMultiDim::Put(double dDate, std::size_t iPath, DVector dValue)
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
void SimulationDataMultiDim::Put(double dDate, std::size_t iPath, std::size_t iDimension, double dValue)
{
    if (dData_.count(dDate) != 0)
    {
        if (dData_.find(dDate)->second.count(iPath) != 0)
        {
            if (dData_.find(dDate)->second.find(iPath)->second.size() > iDimension)
            {
                dData_.find(dDate)->second.find(iPath)->second[iDimension] = dValue;
            }
            else
            {
                dData_.find(dDate)->second.find(iPath)->second.push_back(dValue);
            }
        }
        else
        {
            dData_.find(dDate)->second[iPath] = DVector(iDimension + 1);
            dData_.find(dDate)->second[iPath][iDimension] = dValue;
        }
    }
    else
    {
        dData_[dDate][iPath] = DVector(iDimension + 1);
        dData_[dDate][iPath][iDimension] = dValue;
    }
}

// Getter
std::map<double, std::map<std::size_t, DVector> > SimulationDataMultiDim::GetData() const
{
    return dData_;
}