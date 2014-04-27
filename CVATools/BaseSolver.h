//
//  BaseSolver.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 26/04/14.
//
//

#ifndef __CVATools__BaseSolver__
#define __CVATools__BaseSolver__

#include <iostream>

namespace Utilities
{
    namespace Solvers
    {
        //  Interface class for solvers
        template<typename functor>
        class BaseSolver
        {
        public:
            BaseSolver(const functor & f) : m_f(f)
            {
            }
            
            virtual ~BaseSolver()
            {
            }
            
            virtual double Solve() const = 0;
        protected:
            functor & m_f;
        };
    }
}

#endif /* defined(__CVATools__BaseSolver__) */
