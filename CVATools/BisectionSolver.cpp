//
//  BisectionSolver.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 10/05/14.
//
//

#include "BisectionSolver.h"

namespace Utilities
{
    namespace Solvers
    {
        BisectionParams::BisectionParams() : m_left(0.0), m_right(1.0)
        {}
        
        void BisectionParams::set(const double left, const double right)
        {
            m_left = std::min(left, right);
            m_right = std::max(left, right);
        }
    }
}