//
//  NewtonSolver.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 27/04/14.
//
//

#ifndef __CVATools__NewtonSolver__
#define __CVATools__NewtonSolver__

#include <iostream>
#include "BaseSolver.h"
#include <cmath>
#include "Exception.h"
#include <sstream>

namespace Utilities
{
    namespace Solvers
    {
        struct NewtonParams
        {
            NewtonParams();
            size_t m_iNumIter;
            double m_dTolerance;
            
            double m_dFirstGuess;
            double m_dDerivativeChecks;
        };
        
        template<typename functor>
        class NewtonSolver : public BaseSolver<functor>
        {
        public:
            NewtonSolver(const functor & f, const functor & deriv_, const NewtonParams & params = NewtonParams()) : BaseSolver<functor>(f), m_deriv(deriv_), m_NewtonParams(params)
            {}
            
            ~NewtonSolver()
            {}
            
            virtual double Solve() const
            {
                double res = m_NewtonParams.m_dFirstGuess;
                
                //  Check if first guess is fine
                if (std::abs((BaseSolver<functor>::m_f)(res)) < m_NewtonParams.m_dTolerance)
                {
                    return res;
                }
                
                //  Else launch newton iteration
                size_t iIter = 1;
                while (iIter < m_NewtonParams.m_iNumIter &&
                       std::abs((BaseSolver<functor>::m_f)(res)) > m_NewtonParams.m_dTolerance)
                {
                    double dDeriv = m_deriv(res);
                    if (std::abs(dDeriv) < m_NewtonParams.m_dDerivativeChecks)
                    {
                        std::stringstream ss;
                        ss << "Derivative is too small in Newton Algorithm : iter : " << iIter << " Derivative : " << dDeriv;
                        
                        throw EXCEPTION(ss.str());
                    }
                    res -= (BaseSolver<functor>::m_f)(res) / dDeriv;
                    iIter++;
                }
                
                if (iIter == m_NewtonParams.m_iNumIter)
                {
                    throw EXCEPTION("Newton algorithm has not converged");
                }
                else
                {
                    std::cout << "Newton Algorithm has converged in " << iIter << " iterations." << std::endl;
                }
                
                return res;
            }
        private:
            functor & m_deriv;
            NewtonParams m_NewtonParams;
        };
    }
}

#endif /* defined(__CVATools__NewtonSolver__) */
