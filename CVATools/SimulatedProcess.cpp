//
//  SimulatedProcess.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 30/01/14.
//
//

#include "SimulatedProcess.h"

namespace Finance
{
    namespace Processes
    {
        SimulatedProcess::SimulatedProcess(long long & lSeed)
        {
            m_eng.seed(lSeed);
        }
    }
}