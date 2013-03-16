//
//  Print.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 16/03/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef CVATools_Print_h
#define CVATools_Print_h

#include <vector>
#include <map>
#include "SimulationData.h"

class Print
{
public:
    Print();
    Print(const std::string & cFileName, const bool bAppend, const std::size_t iPrecision);
    virtual ~Print();
    
    virtual void PrintInFile(const std::vector<double> & dData);
    virtual void PrintInFile(const std::vector<std::pair<double, std::size_t> > & dData);
    virtual void PrintInFile(const std::vector<std::pair<double, double> > & dData);
    virtual void PrintInFile(const std::vector<std::vector<double> > & dData);
    virtual void PrintInFile(const std::map<double, std::map<double, double> > & mData);
    virtual void PrintInFile(const std::map<double, std::map<std::size_t, double> > & mData);
protected:
    std::string cFileName_;
    bool bAppend_;
    std::size_t iPrecision_; // number of digits after the point for printing
    std::string cPrecision_; // Conversion of iPrecision_ into a std::string value
};

#endif
