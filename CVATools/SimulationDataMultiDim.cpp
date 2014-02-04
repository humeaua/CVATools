//
//  SimulationDataMultiDim.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 28/03/13.
//
//

#include "SimulationDataMultiDim.h"
#include "Exception.h"

namespace Utilities
{
    //Default constructor
    SimulationDataMultiDim::SimulationDataMultiDim()
    {}
    
    //  Overloading constructor
    SimulationDataMultiDim::SimulationDataMultiDim(const std::vector<double> & dDates, std::size_t iNPaths, std::size_t iNDimensions)
    {
        std::vector<double> sEmptyVector(iNDimensions, 0.0);
        for (std::size_t iDate = 0 ; iDate < dDates.size() ; ++iDate)
        {
            for (std::size_t iPath = 0 ; iPath < iNPaths ; ++iPath)
            {
                dData_[dDates.at(iDate)][iPath] = sEmptyVector;
            }
        }
    }
    
    //  Destructor
    SimulationDataMultiDim::~SimulationDataMultiDim()
    {}
    
    //  Put function
    void SimulationDataMultiDim::Put(double dDate, std::size_t iPath, const Utilities::MyVector<double> & dValue)
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
                dData_.find(dDate)->second[iPath] = Utilities::MyVector<double>(iDimension + 1, 0.0);
                dData_.find(dDate)->second[iPath][iDimension] = dValue;
            }
        }
        else
        {
            dData_[dDate][iPath] = Utilities::MyVector<double>(iDimension + 1, 0.0);
            dData_[dDate][iPath][iDimension] = dValue;
        }
    }
    
    // Getter
    std::map<double, std::map<std::size_t, std::vector<double> > > SimulationDataMultiDim::GetData() const
    {
        return dData_;
    }
    
    Utilities::MyVector<double> SimulationDataMultiDim::GetData(double dDate, std::size_t iPath) const
    {
        if (dData_.count(dDate) != 0)
        {
            std::map<std::size_t, std::vector<double>> dLoc = dData_.find(dDate)->second;
            if (dLoc.count(iPath) != 0)
            {
                return dLoc.find(iPath)->second;
            }
            else
            {
                throw EXCEPTION("SimulationDataMultiDim::GetData : Could not find Path");
            }
        }
        else
        {
            throw EXCEPTION("SimulationDataMultiDim::GetData : Could not find Date");
        }
    }
}