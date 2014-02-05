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
        };
    }
}

#endif /* defined(__CVATools__SVIParameterSolver__) */