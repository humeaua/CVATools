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
            
            void SetFirstGuess(const VolSmile & volSmile);
        };
    }
}

#endif /* defined(__CVATools__SVIParameterSolver__) */
