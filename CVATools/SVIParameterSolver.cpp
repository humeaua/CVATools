//
//  SVIParameterSolver.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 01/02/14.
//
//

#include "SVIParameterSolver.h"
#include "Exception.h"

namespace Finance
{
    namespace Volatility
    {
        SVIParameterSolver::SVIParameterSolver() : dA_(0.0), dB_(0.0), dRho_(0.0), dSigma_(0.0), dM_(0.0)
        {}
        
        void SVIParameterSolver::SetFirstGuess(const VolSmile & volSmile)
        {
            double firstStrike = volSmile.GetFirstStrike(), lastStrike = volSmile.GetLastStrike();
            if (firstStrike < 0.0 && lastStrike > 0.0)
            {
                dM_ = volSmile.GetMeanStrike();
                dSigma_ = volSmile.GetStdDevStrike();
            }
            else
            {
                throw EXCEPTION("First strike must be negative and last strike must be positive");
            }
        }
    }
}