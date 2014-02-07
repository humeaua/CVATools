//
//  SVIParameterSolver.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 01/02/14.
//
//

#include "SVIParameterSolver.h"
#include "Exception.h"
#include "Require.h"

namespace Finance
{
    namespace Volatility
    {
        SVIParameterSolver::SVIParameterSolver() : dA_(0.0), dB_(0.0), dRho_(0.0), dSigma_(0.0), dM_(0.0)
        {}
        
        void SVIParameterSolver::SetFirstGuess(const VolSmile & volSmile, bool useParabola)
        {
            if (useParabola)
            {
                //  need at least 3 strikes for the parabola
                //  check also if the at-the-money volatility is in the volSmile
                REQUIREEXCEPTION(volSmile.IsATMVolQuoted(), "ATM volatility needs to be quoted in volatility smile");
                REQUIREEXCEPTION(volSmile.size() >= 3, "Needs at 3 least quoted strikes");
            }
            double firstStrike = volSmile.GetFirstStrike(), lastStrike = volSmile.GetLastStrike();
            if (firstStrike < 0.0 && lastStrike > 0.0)
            {
                if (!useParabola)
                {
                    dM_ = volSmile.GetMeanStrike();
                    dSigma_ = volSmile.GetStdDevStrike();
                }
                else
                {
                    //  1st guess parametrisation : atm vol + sigma * (log(K/F))^2
                    double atmVol = volSmile(0.0);
                    dSigma_ = ((volSmile(firstStrike) - atmVol) / firstStrike - (volSmile(lastStrike) - atmVol) / lastStrike) / (firstStrike - lastStrike);
                    dM_ = 0.0; // need to check in this case
                    
                    REQUIREEXCEPTION(dSigma_ == 0, "Smile is flat");
                }
            }
            else
            {
                throw EXCEPTION("First strike must be negative and last strike must be positive");
            }
        }
        
        void SVIParameterSolver::Normalize(const std::vector<double> & LogStrikesInput,
                                           const std::vector<double> & volatilitiesInput,
                                           double T, // maturity
                                           std::vector<double> & StrikesOutput,
                                           std::vector<double> & VarianceOutput) const
        {
            REQUIREEXCEPTION(LogStrikesInput.size() == volatilitiesInput.size(), "Inputted Log-strikes and volatilities are not of the same size");
            
            StrikesOutput.resize(LogStrikesInput.size());
            VarianceOutput.resize(LogStrikesInput.size());
            
            std::vector<double>::const_iterator volinput = volatilitiesInput.begin();
            int i = 0;
            for (std::vector<double>::const_iterator strike = LogStrikesInput.begin() ; strike != LogStrikesInput.end() ; ++strike, ++volinput, ++i)
            {
                VarianceOutput[i] = *volinput * *volinput * T;
                StrikesOutput[i] = (*strike - dM_) / dSigma_;
            }
        }

    }
}