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
#include <map>

class RegressionTest;
typedef bool (RegressionTest::* RegressionTestFunction)(std::ostream &);

class RegressionTest {
public:
    bool BondPricing(std::ostream & os);
    bool TimeStatistics(std::ostream & os);
    bool PayoffLinearization(std::ostream & os);
    bool Interpolation(std::ostream & os);
    bool VolatilitySurfaceInterpolation(std::ostream & os);
    bool ProcessPathSimulation(std::ostream & os);
    bool Date(std::ostream & os);
    bool AnalyticFormulae(std::ostream & os);
    bool MatrixInversion(std::ostream & os);
};

class RegressionTestLauncher
{
public:
    bool Launch(std::ostream &out);
    
private:
    void FillMap();
    std::map<std::string, RegressionTestFunction> m_mapping;
    
    RegressionTest m_regTest;
};

#endif /* defined(__CVATools__RegressionTests__) */
