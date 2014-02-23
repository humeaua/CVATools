//
//  SimulationData.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 15/03/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef CVATools_SimulationData_h
#define CVATools_SimulationData_h

#include <iostream>
#include "RegressionData.h"
#include <map>

namespace Utilities
{
    class SimulationData : public RegressionData
    {
    protected:
        std::vector<double> dDates_;
    public:
        SimulationData(std::size_t iNPaths, std::size_t iNDates);
        SimulationData(const std::vector<std::vector<double> > & dData, const std::vector<double> & dDates);
        
        virtual ~SimulationData();

        //  Method to add date in the simulation so that we can keep the dates as well and not only the simulated values
        virtual void AddDate(double dDate);
        
        // Getter for all simulated value for just one date
        virtual std::vector<double> Get(double dDate) const;
        
        //  Method to get the old map of the simulation data class
        virtual std::map<double, std::map<std::size_t, double> > GetData() const;
    };
}

#endif
