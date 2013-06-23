//
//  SimulationData.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 15/03/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef CVATools_SimulationData_h
#define CVATools_SimulationData_h

#include <map>
#include <iostream>

class SimulationData {
protected:
    //        Date,             Path
    std::map<double, std::map<std::size_t, double> > dData_;
    
public:
    
    //Default constructor
    SimulationData();
    
    //  Destructor
    virtual ~SimulationData();
    
    //  Put function
    virtual void Put(double dDate, std::size_t iPath, double dValue);
    
    // Getter 
    virtual std::map<double, std::map<std::size_t, double> > GetData() const;
    virtual double Get(double dDate, std::size_t iPath) const;
    
    //  Apply function
    virtual void Apply(double (*func)(double));
};

#endif
