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
    //m_mapping.insert(std::make_pair("Bond pricing", &RegressionTest::BondPricing));
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
    
    //  Golf tests
    m_mapping.insert(std::make_pair("PlayerResults", &RegressionTest::PlayerResultTest));
    m_mapping.insert(std::make_pair("DummyTournament", &RegressionTest::DummyTournament));
    m_mapping.insert(std::make_pair("StaticDataRanking", &RegressionTest::StaticDataRanking));
    m_mapping.insert(std::make_pair("MultipleTournaments", &RegressionTest::MultipleTournamentsSameWeek));
    m_mapping.insert(std::make_pair("CoSanctionedEvent", &RegressionTest::CoSanctionedTournament));
    m_mapping.insert(std::make_pair("TieHandler", &RegressionTest::TieHandler));
    m_mapping.insert(std::make_pair("Tours", &RegressionTest::Tours));
    m_mapping.insert(std::make_pair("OWGRVectorWrapper", &RegressionTest::OWGRVectorWrapperTest));
    m_mapping.insert(std::make_pair("Major", &RegressionTest::Major));
    m_mapping.insert(std::make_pair("PlayerDispatcher", &RegressionTest::PlayerDispatcher));
    
    //  Random number generators tests
    m_mapping.insert(std::make_pair("Bernouilli", &RegressionTest::Bernouilli));
    m_mapping.insert(std::make_pair("Normal", &RegressionTest::Normal));
    m_mapping.insert(std::make_pair("Discrete Distribution", &RegressionTest::DiscreteDistribution));
    
    //  Utilities tests
    m_mapping.insert(std::make_pair("DoublePrecision", &RegressionTest::DoublePrecision));
    m_mapping.insert(std::make_pair("ConfigLoader", &RegressionTest::ConfigLoaderTest));
    m_mapping.insert(std::make_pair("CSVReader", &RegressionTest::CSVReaderTest));
    m_mapping.insert(std::make_pair("ConfigReader", &RegressionTest::ConfigReaderTest));
    m_mapping.insert(std::make_pair("ConfigReaderPlayer", &RegressionTest::ConfigReaderPlayerTest));
}

RegressionTestLauncher::RegressionTestLauncher(std::ostream & out) : RegressionTest(out)
{
    FillMap();
}

bool RegressionTestLauncher::Launch() const
{
    bool result = true;
    
    //  set the timer
    m_timer = Utilities::Timer();
    //  Iterate along the map
    auto it = m_mapping.begin();
    for ( ; it != m_mapping.end() ; ++it)
    {
        const std::string name = "Regression Test " + it->first;
        m_logger.PutLine(name);
        result = ((*this).*(it->second))();
        if (!result)
        {
            m_logger.PutLine("Regression Test Launcher failed : " + it->first + " test failed!!");
            return result;
        }
        m_logger.AddOneLine();
    }
    m_logger.PutLine("Regression Test Launcher succeeded : all tests succeed");
    m_logger.PutLine(m_timer.TimeElapsed());
    return result;
}