//
//  MathFunctions.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 22/06/13.
//
//

#include "MathFunctions.h"
#include <cmath>
#include "Require.h"

namespace Maths
{
    // Approximation of the cumulative normal function
    double AccCumNorm(double x)
    {
        double dRes;
        double dAbsx = fabs(x);
        double dBuild = 0.0;
        if (dAbsx > 37.0)
        {
            dRes = 0.0;
        }
        else
        {
            double dExp = exp(-dAbsx * dAbsx * 0.5);
            if (dAbsx < 7.07106781186547)
            {
                dBuild = 3.52624965998911E-02 * dAbsx + 0.700383064443688;
                dBuild = dBuild * dAbsx + 6.37396220353165;
                dBuild = dBuild * dAbsx + 33.912866078383;
                dBuild = dBuild * dAbsx + 112.079291497871;
                dBuild = dBuild * dAbsx + 221.213596169931;
                dBuild = dBuild * dAbsx + 220.206867912376;
                
                dRes = dExp * dBuild;
                
                dBuild = 8.83883476483184E-02 * dAbsx + 1.75566716318264;
                dBuild = dBuild * dAbsx + 16.064177579207;
                dBuild = dBuild * dAbsx + 86.7807322029461;
                dBuild = dBuild * dAbsx + 296.564248779674;
                dBuild = dBuild * dAbsx + 637.333633378831;
                dBuild = dBuild * dAbsx + 793.826512519948;
                dBuild = dBuild * dAbsx + 440.413735824752;
                
                dRes /= dBuild;
            }
            else
            {
                dBuild = dAbsx + 0.65;
                dBuild = dAbsx + 4.0 / dBuild;
                dBuild = dAbsx + 3.0 / dBuild;
                dBuild = dAbsx + 2.0 / dBuild;
                dBuild = dAbsx + 1.0 / dBuild;
                dRes = dExp / dBuild / 2.506628274631;
            }
        }
        if (x > 0)
        {
            return 1.0 - dRes;
        }
        else
        {
            return dRes;
        }
    }
    
    // Approximation of the Debye function
    DebyeFunction::DebyeFunction() : m_epsilon(0.001), m_nbStepInt(0.001), m_error(1e-10)
    {}
    
    double DebyeFunction::operator()(double x, double k) const
    {
        // Check for exception values
        REQUIREEXCEPTION(k < 3, "Cannot compute Debye function for k >= 2");
        REQUIREEXCEPTION(fabs(x) > m_epsilon, "x is too small");
        
        double dRes = 0.0;
        if (x > 0)
        {
            // case i = 0
            dRes += pow(m_epsilon,k-1.0);
            double dx = m_epsilon;
            for ( ; dx < x ; dx += m_nbStepInt)
            {
                dRes += pow(dx, k) / (exp(dx)-1.0) * m_nbStepInt;
            }
            dx -= m_nbStepInt;
            dRes += pow(dx, k) / (exp(dx)-1.0) * (x - dx);
        }
        else
        { 
            REQUIREEXCEPTION(fabs(k - static_cast<int>(k)) > m_error,  "Power has to be an integer when computing Debye function for negative value");
            // case i = 0
            dRes -= pow(m_epsilon,k-1.0);
            double dx = m_epsilon;
            for ( ; dx < x ; dx -= m_nbStepInt)
            {
                dRes -= pow(dx, k) / (exp(dx)-1.0) * m_nbStepInt;
            }
            dx -= m_nbStepInt;
            dRes += pow(dx, k) / (exp(dx)-1.0) * (x - dx);
            
        }
        return dRes * k / pow(x, k);
    }
}