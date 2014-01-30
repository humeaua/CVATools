//
//  SimulatedProcessMultiDim.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 30/01/14.
//
//

#include "SimulatedProcessMultiDim.h"

namespace Finance
{
    namespace Processes
    {
        SimulatedProcessMultiDim::SimulatedProcessMultiDim(long long & lSeed)
        {
            m_eng.seed(lSeed);
        }
    }
}