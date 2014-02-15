//
//  Analytic.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 15/02/14.
//
//

#include "Analytic.h"
#include "MathFunctions.h"
#include <cmath>
#include "Exception.h"
#include "MathConstants.h"

namespace Finance
{
    namespace Pricers
    {
        double Analytic::d1(double forward,
                            double strike,
                            double volatility,
                            double maturity) const
        {
            return log(forward / strike) / (volatility * sqrt(maturity)) + 0.5 * volatility * sqrt(maturity);
        }
        
        double Analytic::d2(double forward,
                            double strike,
                            double volatility,
                            double maturity) const
        {
            return log(forward / strike) / (volatility * sqrt(maturity)) + 0.5 * volatility * sqrt(maturity);
        }
        
        void Analytic::CheckParameters() const
        {
            throw EXCEPTION("Not yet implemented");
        }

        double Analytic::VanillaPrice(double forward,
                                      double strike,
                                      double volatility,
                                      double maturity,
                                      double rate,
                                      Finance::Payoff::VanillaOptionType optionType) const
        {
            const double l_d1 = d1(forward, strike, volatility, maturity), l_d2 = d2(forward, strike, volatility, maturity);
            
            if (optionType == Finance::Payoff::CALL)
            {
                return (forward * Maths::AccCumNorm(l_d1) - strike * Maths::AccCumNorm(l_d2)) * exp(-rate * maturity);
            }
            else if (optionType == Finance::Payoff::PUT)
            {
                return (strike * Maths::AccCumNorm(-l_d2) - forward * Maths::AccCumNorm(-l_d1)) * exp(-rate * maturity);
            }
            else // straddle
            {
                return (forward * Maths::AccCumNorm(l_d1) - strike * Maths::AccCumNorm(l_d2) +
                        strike * Maths::AccCumNorm(-l_d2) - forward * Maths::AccCumNorm(-l_d1)) * exp(-rate * maturity);
            }
        }
        
        double Analytic::VegaVanillaOption(double forward,
                                           double strike,
                                           double volatility,
                                           double maturity,
                                           double rate,
                                           Finance::Payoff::VanillaOptionType optionType) const
        {
            const double l_d1 = d1(forward, strike, volatility, maturity);
            const double vega = exp(-rate * maturity) * forward * exp(-0.5 * l_d1 * l_d1) * ONE_OVER_SQUARE_ROOT_OF_2_PI * sqrt(maturity);
            if (optionType == Finance::Payoff::STRADDLE)
            {
                return 2.0 * vega;
            }
            else
            {
                return vega;
            }
        }
        
        double Analytic::DigitalPrice(double forward,
                                      double strike,
                                      double volatility,
                                      double maturity,
                                      double rate,
                                      Finance::Payoff::VanillaOptionType optionType) const
        {
            if (optionType == Finance::Payoff::STRADDLE)
            {
                //  Digital straddle pays 1, so is equal to zero-coupon bond
                return exp(-rate * maturity);
            }
            else if (optionType == Finance::Payoff::CALL)
            {
                const double l_d1 = d1(forward, strike, volatility, maturity);
                return exp(-rate * maturity) * Maths::AccCumNorm(l_d1);
            }
            else // put
            {
                const double l_d2 = d2(forward, strike, volatility, maturity);
                return exp(-rate * maturity) * Maths::AccCumNorm(l_d2);
            }
        }
        
        double Analytic::DigitalPrice(double forward,
                                      double strike,
                                      const Finance::Volatility::VolSmile & volSmile,
                                      double maturity,
                                      double rate,
                                      Finance::Payoff::VanillaOptionType optionType) const
        {
            if (optionType == Finance::Payoff::STRADDLE)
            {
                //  Digital straddle pays 1, so is equal to zero-coupon bond
                return exp(-rate * maturity);
            }
            else
            {
                const double volatility = volSmile(strike);
                double noSmiledPrice = 0.0;
                if (optionType == Finance::Payoff::CALL)
                {
                    const double l_d1 = d1(forward, strike, volatility, maturity);
                    noSmiledPrice = exp(-rate * maturity) * Maths::AccCumNorm(l_d1);
                }
                else // put
                {
                    const double l_d2 = d2(forward, strike, volatility, maturity);
                    noSmiledPrice = exp(-rate * maturity) * Maths::AccCumNorm(l_d2);
                }
                return noSmiledPrice - volSmile.skew(strike) * VegaVanillaOption(forward, strike, volatility, maturity, rate, optionType);
            }
        }
    }
}