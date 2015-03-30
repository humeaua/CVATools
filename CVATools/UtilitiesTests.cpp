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
        m_out << "SUCCEEDED" << std::endl;
        return true;
    }
    else
    {
        m_out << "FAILED" << std::endl;
        return false;
    }
}

bool RegressionTest::ConfigLoaderTest() const
{
    const std::string filename = "\\";
    class ConfigLoader<OWGRWrapperLoader<double> > loader(filename);
    
    return true;
}

bool RegressionTest::CSVReaderTest() const
{
    const std::string filename = "//Users//alexhum49//Documents//Workspace//CVA//CVATools//Input//OWGR//Tests//TestCSV1.csv";
    std::ifstream file(filename.c_str());
    CSVReader<double> csvReader(filename);
    
    std::vector<double> values = *csvReader;
    double refValues[] = {1,0};
    const double tolerance = 1e-10;
    double error = 0.0;
    for (size_t i = 0 ; i < values.size() ; ++i)
    {
        error += std::abs( values[i] -refValues[i]);
    }
    
    if (error < tolerance)
    {
        m_out << "SUCCEEDED" << std::endl;
        return true;
    }
    else
    {
        m_out << "FAILED" << std::endl;
        return false;
    }
}