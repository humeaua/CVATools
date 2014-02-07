//
//  SVIParameterSolver.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 01/02/14.
//
//

#ifndef __CVATools__SVIParameterSolver__
#define __CVATools__SVIParameterSolver__

#include <iostream>
#include "VolSmile.h"
#include "Matrix.h"

namespace Finance
{
    namespace Volatility
    {
        class SVIParameterSolver
        {
        protected:
            double dA_, dB_, dRho_, dSigma_, dM_;
            
        public:
            SVIParameterSolver();
            
            //  The parameter useParabola controls the fact that the parameters m and sigma are choosen by fitting a parabola, using the first quoted strike, the last quoted strike and the at-the-money volatility
            void SetFirstGuess(const VolSmile & volSmile, bool useParabola);
            
            //  The goal of the method is to normalize the volatilities and the strikes to apply the SVI resolution
            void Normalize(const std::vector<double> & LogStrikesInput,
                           const std::vector<double> & volatilitiesInput,
                           double T, // maturity
                           std::vector<double> & StrikesOutput,
                           std::vector<double> & VarianceOutput) const;
            
            void ComputeRHS(const std::vector<double> & NormalizedLogStrikes,
                            const std::vector<double> & Variance,
                            std::vector<double> & RHS) const;
            
            void ComputeLHSMatrix(const std::vector<double> & NormalizedLogStrikes,
                                  Utilities::Matrix<double> & LHSMatrix) const;
            
            void Solve(const std::vector<double> & LogStrikesInput,
                       const std::vector<double> & volatilitiesInput,
                       double T); // maturity
        };
    }
}

#endif /* defined(__CVATools__SVIParameterSolver__) */
