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
    bool MyException() const;
    bool PayoffParser() const;
    bool DefaultArguments() const;
    bool GaussianKernel() const;
    bool MargrabeOptionVasicek() const;
    
    //  Golf unit testing
    bool PlayerResultTest() const;
    bool DummyTournament() const;
    bool StaticDataRanking() const;
    bool MultipleTournamentsSameWeek() const;
    bool CoSanctionedTournament() const;
    bool TieHandler() const;
};

#endif /* defined(__CVATools__RegressionTests__) */
