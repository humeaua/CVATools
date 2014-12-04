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
typedef bool (RegressionTest::* RegressionTestFunction)() const;

class RegressionTest {
protected:
    std::ostream & m_out;
public:
    RegressionTest(std::ostream & os);
    bool BondPricing() const;
    bool TimeStatistics() const;
    bool PayoffLinearization() const;
    bool Interpolation() const;
    bool VolatilitySurfaceInterpolation() const;
    bool ProcessPathSimulation() const;
    bool Date() const;
    bool AnalyticFormulae() const;
    bool MatrixInversion() const;
    bool NewtonSolver() const;
    bool Ticker() const;
    bool Sobol() const;
    bool DebyeFunction() const;
    bool Statistic() const;
    bool muParser() const;
};

class RegressionTestLauncher : public RegressionTest
{
public:
    RegressionTestLauncher(std::ostream & out);
    bool Launch() const;
    
private:
    void FillMap();
    Utilities::HashTable<std::string, RegressionTestFunction> m_mapping;
};

#endif /* defined(__CVATools__RegressionTests__) */
