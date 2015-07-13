//
//  UtilitiesTests.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 28/02/15.
//
//

#include "RegressionTests.h"
#include "DoublePrecision.h"
#include <cmath>
#include "ConfigLoader.h"
#include "OWGRWrapperLoader.h"
#include "CSVReader.h"

#include "StringUtilities.h"
#include "ConfigReader.h"
#include "Player.h"

bool RegressionTest::DoublePrecision() const
{
    const double pi = 3.14159265359;
    
    const double tolerance = 1e-15;
    const double refValue = 3.14;
    const int refValueint = 3;
    const double pi_2 = Precision<2, double>(pi);
    const int pi_0 = Precision<0, int>(pi);
    const double error = fabs(refValue-pi_2) + std::abs(refValueint-pi_0);
    
    if (error < tolerance)
    {
        m_logger.PutLine("SUCCEEDED");
        return true;
    }
    else
    {
        m_logger.PutLine("FAILED");
        return false;
    }
}

bool RegressionTest::ConfigLoaderTest() const
{
    const std::string filename = "//Users//alexhum49//Documents//Workspace//CVA//CVATools//Input//OWGR//Tests//TestConfigLoader.csv";
    ConfigLoader<OWGRWrapperLoader<double> > loader(filename);
    
    const OWGRVectorWrapper<double> & obj = loader.get().get();
    const double refValues[] = {1, 2, 34, 4.2, 5, 6.28};
    double error = 0.0;
    const double tolerance = 1e-10;
    for (size_t i = 0 ; i < obj.size() ; ++i)
    {
        error += std::abs(obj[i] - refValues[i]);
    }
    
    if (error > tolerance)
    {
        m_logger.PutLine("FAILED");
        return false;
    }
    else
    {
        m_logger.PutLine("SUCCEEDED");
        return true;
    }
}

bool RegressionTest::CSVReaderTest() const
{
    const std::string filename = "//Users//alexhum49//Documents//Workspace//CVA//CVATools//Input//OWGR//Tests//TestCSV1.txt";
    std::ifstream file(filename.c_str());
    CSVReader csvReader(filename);
    
    std::vector<double> values;
    csvReader >> values;
    double refValues[] = {1,0};
    const double tolerance = 1e-10;
    double error = 0.0;
    const size_t size = values.size();
    if (size != 2)
    {
        throw EXCEPTION("values should be of size 2");
    }
    for (size_t i = 0 ; i < size ; ++i)
    {
        error += std::abs( values[i] -refValues[i]);
    }
    
    if (error < tolerance)
    {
        m_logger.PutLine("SUCCEEDED");
        return true;
    }
    else
    {
        m_logger.PutLine("FAILED");
        return false;
    }
}

bool RegressionTest::ConfigReaderTest() const
{
    // to be written
    const std::string filename ="//Users//alexhum49//Documents//Workspace//CVA//CVATools//Input//OWGR//Tests//TestConfigReader.txt";
    
    ConfigReader configReader(filename);
    PlayerID playerId("", Utilities::Date::MyDate());
    
    const std::string refValue = "Alexandre";
    configReader.Fill(playerId, "PlayerID");
    
    if (playerId.Name() == refValue /*&& playerId.BirthDate() == Utilities::Date::MyDate(25,4,1989)*/)
    {
        m_logger.PutLine("SUCCEEDED");
        return true;
    }
    else
    {
        m_logger.PutLine("FAILED");
        return false;
    }
}

bool RegressionTest::ConfigReaderPlayerTest() const
{
    const std::string filename ="//Users//alexhum49//Documents//Workspace//CVA//CVATools//Input//OWGR//Tests//TestConfigReaderPlayer.txt";
    
    ConfigReader configReader(filename);
    Player player("",TourType(1), Utilities::Date::MyDate());
    
    const std::string refValue = "Alexandre";
    configReader.Fill(player, "Player");
    if (player.Name() == refValue /*&& player.BirthDate() == Utilities::Date::MyDate(25,4,1989)*/)
    {
        m_logger.PutLine("SUCCEEDED");
        return true;
    }
    else
    {
        m_logger.PutLine("FAILED");
        return false;
    }
}