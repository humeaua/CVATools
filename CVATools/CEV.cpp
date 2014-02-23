//
//  CEV.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 23/02/14.
//
//

#include "CEV.h"
#include <cmath>

namespace Finance
{
    namespace Processes
    {
        CEV::CEV(double beta, double x0, long long & lSeed) : LocalVolatility(x0, lSeed), m_beta(beta)
        {}
        
        double CEV::SigmaLoc(double t, double S) const
        {
            return pow(S, m_beta);
        }
        
        double CEV::drift(double t, double S) const
        {
            return 0.0;
        }
    }
}