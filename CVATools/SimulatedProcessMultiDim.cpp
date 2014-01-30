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
        SimulatedProcessMultiDim::SimulatedProcessMultiDim(long long & lSeed) : m_eng(new std::tr1::ranlux64_base_01)
        {
            m_eng->seed(lSeed);
        }
    }
}