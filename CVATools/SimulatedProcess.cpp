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
        SimulatedProcess::SimulatedProcess(long long & lSeed) : m_eng(new std::tr1::ranlux64_base_01)
        {
            m_eng->seed(lSeed);
        }
    }
}