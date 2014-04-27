//
//  NewtonSolver.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 27/04/14.
//
//

#include "NewtonSolver.h"

namespace Utilities
{
    namespace Solvers
    {
        NewtonParams::NewtonParams() : m_iNumIter(100), m_dTolerance(1e-7), m_dFirstGuess(0.0), m_dDerivativeChecks(1e-8)
        {}
    }
}