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

bool RegressionTest::DoublePrecision() const
{
    const double pi = 3.14159265359;
    
    const double tolerance = 1e-15;
    const double refValue = 3.14;
    const double pi_2 = Precision<2>(pi);
    const double error = fabs(refValue-pi_2);
    
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
