//
//  VolSmile.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 31/01/14.
//
//

#include "VolSmile.h"
#include <cmath>
#include "Require.h"
#include "MathFunctions.h"
#include "VectorUtilities.h"
#include <sstream>

namespace Finance
{
    namespace Volatility
    {
        VolSmile::VolSmile(const std::vector<double> & dStrikes,
                           const std::vector<double> & dVolatilities,
                           double dFwdRef,
                           double T) : Utilities::Interp::HermiteDegree5Interpolator(dStrikes, dVolatilities), dFwdRef_(dFwdRef), dMaturity_(T)
        {
            REQUIREEXCEPTION(T >= 0.0, "Maturity is negative");
            REQUIREEXCEPTION(dFwdRef_ > 0, "Reference forward is negative");
            for (std::size_t i = 0 ; i < dVariables_.size() ; ++i)
            {
                if (dVariables_[i] < 0.0)
                {
                    std::stringstream ss;
                    ss << "Variable at index " << i << " is negative. Value : " << dVariables_[i];
                    throw EXCEPTION(ss.str());
                }
                dVariables_[i] = log(dVariables_[i] / dFwdRef_);
            }
        }
        
        bool VolSmile::CheckButterflySpreadArbitrage() const
        {
            double dOldStrike0 = dFwdRef_ * exp(dVariables_[0]), dOldStrike1 = dFwdRef_ * exp(dVariables_[1]);
            for (std::size_t i = 1 ; i < dVariables_.size() - 1 ; ++i)
            {
                double Strike = dFwdRef_ * exp(dVariables_[i+1]);
                
                if (CallPrice(dOldStrike0) + CallPrice(Strike) - 2.0 * CallPrice(dOldStrike1) < 0.0)
                {
                    std::cout << "Butterfly spread arbitrage at strike " << dOldStrike1 << " and maturity T = " << dMaturity_ << " year" << std::endl;
                    std::cout << "Call price (K = " << dOldStrike0 << ") : " << CallPrice(dOldStrike0) << std::endl;
                    std::cout << "Call price (K = " << dOldStrike1 << ") : " << CallPrice(dOldStrike1) << std::endl;
                    std::cout << "Call price (K = " << Strike << ") : " << CallPrice(Strike) << std::endl;
                    return false;
                }
                dOldStrike0 = dOldStrike1;
                dOldStrike1 = Strike;
            }
            return true;
        }
        
        double VolSmile::CallPrice(double K) const
        {
            REQUIREEXCEPTION(K > 0, "Strike is negative");
            const double logFwdOverStrike = log(dFwdRef_ / K);
            const double volatility = (*this)(K);
            if (volatility == 0.0)
            {
                return std::max(dFwdRef_ - K, 0.0);
            }
            const double d1 = logFwdOverStrike / (volatility * sqrt(dMaturity_)) + 0.5 * volatility * sqrt(dMaturity_), d2 = d1 - volatility * sqrt(dMaturity_);
            
            return dFwdRef_ * Maths::AccCumNorm(d1) - K * Maths::AccCumNorm(d2);
        }
        
        bool VolSmile::IsArbitrageFree() const
        {
            return CheckButterflySpreadArbitrage();
        }
        
        double VolSmile::GetFirstStrike() const
        {
            return dVariables_.front();
        }
        
        double VolSmile::GetLastStrike() const
        {
            return dVariables_.back();
        }
        
        double VolSmile::GetMeanStrike() const
        {
            return Utilities::Mean<double, double>(dVariables_);
        }
        
        double VolSmile::GetStdDevStrike() const
        {
            return Utilities::StdDev<double, double>(dVariables_);
        }
        
        double VolSmile::FwdRef() const
        {
            return dFwdRef_;
        }
        
        double VolSmile::Maturity() const
        {
            return dMaturity_;
        }
        
        bool VolSmile::IsATMVolQuoted() const
        {
            //  If not found, the function FindInVector returns -1;
            return Utilities::GetIndex(dVariables_, 0.0) != -1;
        }
        
        double VolSmile::operator()(double strike) const
        {
            //  Flat extrapolation in concordance with Roger Lee moment formula
            REQUIREEXCEPTION(strike > 0.0, "Strike is negative");
            const double logstrike = log(strike / dFwdRef_);
            if (logstrike < GetFirstStrike())
            {
                return dValues_.front();
            }
            else if (logstrike > GetLastStrike())
            {
                return dValues_.back();
            }
            else
            {
                return HermiteDegree5Interpolator::operator()(logstrike);
            }
        }
        
        double VolSmile::skew(double strike) const
        {
            REQUIREEXCEPTION(strike > 0.0, "Strike is negative");
            //  Flat extrapolation in concordance with Roger Lee moment formula
            const double logstrike = log(strike / dFwdRef_);
            if (logstrike < GetFirstStrike() || logstrike > GetLastStrike())
            {
                return 0.0;
            }
            else
            {
                return HermiteDegree5Interpolator::PointDerivative(logstrike) / strike;
            }
        }
        
        double VolSmile::volatilityConvexity(double strike) const
        {
            REQUIREEXCEPTION(strike > 0.0, "Strike is negative");
            //  Flat extrapolation in concordance with Roger Lee moment formula
            const double logstrike = log(strike / dFwdRef_);
            if (logstrike < GetFirstStrike() || logstrike > GetLastStrike())
            {
                return 0.0;
            }
            else
            {
                return (HermiteDegree5Interpolator::PointConvexity(logstrike) - HermiteDegree5Interpolator::PointDerivative(logstrike)) / strike / strike;
            }
        }
        
        std::vector<double> VolSmile::LogStrikes() const
        {
            return dVariables_;
        }
        
        std::vector<double> VolSmile::Volatilities() const
        {
            return dValues_;
        }
    }
}