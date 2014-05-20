//
//  BisectionSolver.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 10/05/14.
//
//

#ifndef __CVATools__BisectionSolver__
#define __CVATools__BisectionSolver__

#include <iostream>
#include "BaseSolver.h"

namespace Utilities
{
    namespace Solvers
    {
        struct BisectionParams
        {
            double m_left, m_right;
            BisectionParams();
            
            void set(const double left, const double right);
        };
        
        template<typename functor>
        class BisectionSolver : public BaseSolver<functor>
        {
        public:
            BisectionSolver(const functor & f, const BisectionParams & params = BisectionParams()) : BaseSolver<functor>(f), m_Params(params)
            {}
            
            virtual ~BisectionSolver()
            {}
            
            virtual double Solve() const
            {
                
            }
            
        private:
            BisectionParams m_Params;
        };
    }
}

#endif /* defined(__CVATools__BisectionSolver__) */
