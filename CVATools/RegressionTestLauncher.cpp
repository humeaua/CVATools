//
//  RegressionTestLauncher.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 11/01/15.
//
//

#include "RegressionTestLauncher.h"

/////////////////////////////////////////////////////
//
//      Regression test launcher
//
/////////////////////////////////////////////////////

void RegressionTestLauncher::FillMap()
{
    m_mapping.insert(std::make_pair("Analytic", &RegressionTest::AnalyticFormulae));
    m_mapping.insert(std::make_pair("VolatilitySurface", &RegressionTest::VolatilitySurfaceInterpolation));
    m_mapping.insert(std::make_pair("Date", &RegressionTest::Date));
    m_mapping.insert(std::make_pair("Process Path Simulation", &RegressionTest::ProcessPathSimulation));
    m_mapping.insert(std::make_pair("Payoff linearization", &RegressionTest::PayoffLinearization));
    m_mapping.insert(std::make_pair("Interpolation", &RegressionTest::Interpolation));
    m_mapping.insert(std::make_pair("Time Statistics", &RegressionTest::TimeStatistics));
    m_mapping.insert(std::make_pair("Bond pricing", &RegressionTest::BondPricing));
    m_mapping.insert(std::make_pair("Matrix inversion", &RegressionTest::MatrixInversion));
    m_mapping.insert(std::make_pair("Newton Solver", &RegressionTest::NewtonSolver));
    m_mapping.insert(std::make_pair("Ticker", &RegressionTest::Ticker));
    m_mapping.insert(std::make_pair("Sobol", &RegressionTest::Sobol));
    m_mapping.insert(std::make_pair("Debye Function", &RegressionTest::DebyeFunction));
    m_mapping.insert(std::make_pair("Statistic", &RegressionTest::Statistic));
    m_mapping.insert(std::make_pair("muParser", &RegressionTest::muParser));
    m_mapping.insert(std::make_pair("Exception", &RegressionTest::MyException));
    m_mapping.insert(std::make_pair("PayoffParser", &RegressionTest::PayoffParser));
    m_mapping.insert(std::make_pair("DefaultArguments", &RegressionTest::DefaultArguments));
    m_mapping.insert(std::make_pair("GaussianKernel", &RegressionTest::GaussianKernel));
    m_mapping.insert(std::make_pair("MargrabeOption", &RegressionTest::MargrabeOptionVasicek));
    m_mapping.insert(std::make_pair("PlayerResults", &RegressionTest::PlayerResultTest));
    m_mapping.insert(std::make_pair("DummyTournament", &RegressionTest::DummyTournament));
    m_mapping.insert(std::make_pair("StaticDataRanking", &RegressionTest::StaticDataRanking));
    m_mapping.insert(std::make_pair("MultipleTournaments", &RegressionTest::MultipleTournamentsSameWeek));
}

RegressionTestLauncher::RegressionTestLauncher(std::ostream & out) : RegressionTest(out)
{
    FillMap();
}

bool RegressionTestLauncher::Launch() const
{
    bool result = true;
    
    //  Iterate along the map
    auto it = m_mapping.begin();
    for ( ; it != m_mapping.end() ; ++it)
    {
        m_out << "Regression Test " << it->first << std::endl;
        result = ((*this).*(it->second))();
        if (!result)
        {
            return result;
        }
        m_out << std::endl;
    }
    return result;
}