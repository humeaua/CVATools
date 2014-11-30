//
//  RegressionTests.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 26/05/13.
//
//

#ifndef __CVATools__RegressionTests__
#define __CVATools__RegressionTests__

#include <iostream>
#include "HashTable.h"

class RegressionTest;
typedef bool (RegressionTest::* RegressionTestFunction)(std::ostream &) const;

class RegressionTest {
public:
    bool BondPricing(std::ostream & os) const;
    bool TimeStatistics(std::ostream & os) const;
    bool PayoffLinearization(std::ostream & os) const;
    bool Interpolation(std::ostream & os) const;
    bool VolatilitySurfaceInterpolation(std::ostream & os) const;
    bool ProcessPathSimulation(std::ostream & os) const;
    bool Date(std::ostream & os) const;
    bool AnalyticFormulae(std::ostream & os) const;
    bool MatrixInversion(std::ostream & os) const;
    bool NewtonSolver(std::ostream & os) const;
    bool Ticker(std::ostream & os) const;
    bool Sobol(std::ostream & os) const;
    bool DebyeFunction(std::ostream & os) const;
    bool Statistic(std::ostream & os) const;
    bool muParser(std::ostream & os) const;
};

class RegressionTestLauncher
{
public:
    RegressionTestLauncher(std::ostream & out);
    bool Launch() const;
    
private:
    void FillMap();
    Utilities::HashTable<std::string, RegressionTestFunction> m_mapping;
    
    RegressionTest m_regTest;
    std::ostream & m_out;
};

#endif /* defined(__CVATools__RegressionTests__) */
