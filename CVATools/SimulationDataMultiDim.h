//
//  SimulationDataMultiDim.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 28/03/13.
//
//

#ifndef CVATools_SimulationDataMultiDim_h
#define CVATools_SimulationDataMultiDim_h

#include <vector>
#include <map>
#include "Type.h"

class SimulationDataMultiDim {
protected:
    //        Date,             Path
    std::map<double, std::map<std::size_t, DVector > > dData_;
    
public:
    //Default constructor
    SimulationDataMultiDim();
    
    //Overloading constructor
    SimulationDataMultiDim(const std::vector<double> & dDates, std::size_t iNPaths, std::size_t iDimension);
    
    //  Destructor
    virtual ~SimulationDataMultiDim();
    
    //  Put function
    virtual void Put(double dDate, std::size_t iPath, DVector dValue);
    virtual void Put(double dDate, std::size_t iPath, std::size_t iDimension, double dValue);
    
    // Getter
    virtual std::map<double, std::map<std::size_t, DVector> > GetData() const;
    virtual DVector GetData(double dDate, std::size_t iPath) const;
    
    //  Apply functions
    virtual void Apply(double (*func)(double));
};

#endif
