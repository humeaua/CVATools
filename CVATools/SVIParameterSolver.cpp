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
#include <cmath>
#include <sstream>

namespace Finance
{
    namespace Volatility
    {
        SVIParameterSolver::SVIParameterSolver(double dFwdRef) : dA_(0.0), dB_(0.0), dRho_(0.0), dSigma_(0.0), dM_(0.0), dFwdRef_(dFwdRef)
        {}
        
        SVIParameterSolver::~SVIParameterSolver()
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
                    double atmVol = volSmile(dFwdRef_);
                    //  We call the operator as first strike and last strike are quoted as logstrikes
                    dSigma_ = ((volSmile.Utilities::Interp::HermiteSplineCubicInterpolator::operator()(firstStrike) - atmVol) / firstStrike - (volSmile.Utilities::Interp::HermiteSplineCubicInterpolator::operator()(lastStrike) - atmVol) / lastStrike) / (firstStrike - lastStrike);
                    dM_ = 0.0; // need to check in this case
                    
                    REQUIREEXCEPTION(dSigma_ != 0, "Smile is flat");
                }
            }
            else
            {
                std::stringstream ss;
                if (firstStrike > 0.0)
                {
                    ss << "First strike must be negative. Current value " << firstStrike << ". ";
                }
                if (lastStrike < 0.0)
                {
                    ss << "Last strike must be positive. Current value " << lastStrike << ".";
                }
                throw EXCEPTION(ss.str());
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
        
        void SVIParameterSolver::ComputeRHS(const std::vector<double> &NormalizedLogStrikes, const std::vector<double> &Variance, std::vector<double> &RHS) const
        {
            for (std::size_t i = 0 ; i < NormalizedLogStrikes.size() ; ++i)
            {
                RHS[0] += Variance[i];
                RHS[1] += Variance[i] * NormalizedLogStrikes[i];
                RHS[2] += Variance[i] * sqrt(1 + NormalizedLogStrikes[i] * NormalizedLogStrikes[i]);
            }
        }
        
        void SVIParameterSolver::ComputeLHSMatrix(const std::vector<double> &NormalizedLogStrikes, Utilities::Matrix<double> &LHSMatrix) const
        {
            for (std::size_t i = 0 ; i < NormalizedLogStrikes.size() ; ++i)
            {
                LHSMatrix(0,1) += NormalizedLogStrikes[i];
                LHSMatrix(0,2) += sqrt(1 + NormalizedLogStrikes[i] * NormalizedLogStrikes[i]);
                LHSMatrix(1,2) += NormalizedLogStrikes[i] * sqrt(1 + NormalizedLogStrikes[i] * NormalizedLogStrikes[i]);
                LHSMatrix(1,1) += NormalizedLogStrikes[i] * NormalizedLogStrikes[i];
            }
            LHSMatrix(0,0) = NormalizedLogStrikes.size();
            LHSMatrix(2,2) = LHSMatrix(0,0) + LHSMatrix(1,1);
            LHSMatrix(2,0) = LHSMatrix(0,2);
            LHSMatrix(2,1) = LHSMatrix(1,2);
            LHSMatrix(1,0) = LHSMatrix(0,1);

        }
        
        void SVIParameterSolver::Solve(const Finance::Volatility::VolSmile & volSmile, bool useParabola)
        {
            //  Set First guess
            SetFirstGuess(volSmile, useParabola);
            
            //  apply solver
            Solve(volSmile.LogStrikes(), volSmile.Volatilities(), volSmile.Maturity());
        }
        
        void SVIParameterSolver::Solve(const std::vector<double> & LogStrikesInput,
                                       const std::vector<double> & volatilitiesInput,
                                       double T)// maturity
        {
            std::vector<double> NormalizedLogStrikes, Variance, RHS(3), Params(3);
            Utilities::Matrix<double> LHS(3,3), LHSInverse(3,3);
            
            //  Normalize variables
            Normalize(LogStrikesInput, volatilitiesInput, T, NormalizedLogStrikes, Variance);
            
            //  Compute coefficients of linear system
            ComputeLHSMatrix(NormalizedLogStrikes, LHS);
            ComputeRHS(NormalizedLogStrikes, Variance, RHS);
            
            //  Invert matrix
            Utilities::matrixinverse(LHSInverse, LHS);
            
            //  Multiply inverted matrix by rhs
            Utilities::mult(Params, LHSInverse, RHS);
            
            dA_ = Params[0] / T;
            dRho_ = Params[1] / Params[2];
            dB_ = Params[2] / (dSigma_ * T);
        }
        
        double SVIParameterSolver::operator()(double strike) const
        {
            double logStrike = log(strike / dFwdRef_);
            double volsquare = dA_ + dB_ * (dRho_ * (logStrike - dM_) + sqrt((logStrike - dM_) * (logStrike - dM_) + dSigma_ * dSigma_));
            if (volsquare < 0)
            {
                std::stringstream ss;
                ss << "Variance is negative for strike K : " << strike ;
                throw EXCEPTION(ss.str());
            }
            return sqrt(volsquare);
        }
        
        bool SVIParameterSolver::IsArbitrable(double T) const
        {
            if (!(dB_ * T <= 4.0 && dB_ >= 0))
            {
                std::cout << "B : " << dB_ << std::endl;
                return true;
            }
            if (!(fabs(dRho_) < 1.0))
            {
                std::cout << "Rho : " << dRho_ << std::endl;
                return true;
            }
            if (!(fabs(dRho_ * dB_ * dSigma_ * T)< 4.0 * dSigma_ - dB_ * dSigma_ * T))
            {
                std::cout << "Rho : " << dRho_ << std::endl;
                std::cout << "B : " << dB_ << std::endl;
                std::cout << "Sigma : " << dSigma_ << std::endl;
                return true;
            }
            return false;
        }
    }
}