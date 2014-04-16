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
            return log(forward / strike) / (volatility * sqrt(maturity)) - 0.5 * volatility * sqrt(maturity);
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
        
        double Analytic::VolgaVanillaOption(double forward,
                                            double strike,
                                            double volatility,
                                            double maturity,
                                            double rate,
                                            Finance::Payoff::VanillaOptionType optionType) const
        {
            return VegaVanillaOption(forward, strike, volatility, maturity, rate, optionType) * d1(forward, strike, volatility, maturity) * d2(forward, strike, volatility, maturity) / volatility;
        }
        
        double Analytic::d2CalldVolatilitydStrike(double forward,
                                                  double strike,
                                                  double volatility,
                                                  double maturity,
                                                  double rate,
                                                  Finance::Payoff::VanillaOptionType optionType) const
        {
            return VegaVanillaOption(forward, strike, volatility, maturity, rate, optionType) * d1(forward, strike, volatility, maturity) / (strike * volatility * sqrt(maturity));
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
                std::cout << "Straddle case = Zero coupon bond : paying one unit of domestic currency at maturity" << std::endl;
                return exp(-rate * maturity);
            }
            else if (optionType == Finance::Payoff::CALL)
            {
                const double l_d2 = d2(forward, strike, volatility, maturity);
                return exp(-rate * maturity) * Maths::AccCumNorm(l_d2);
            }
            else // put
            {
                const double l_d1 = d1(forward, strike, volatility, maturity);
                return exp(-rate * maturity) * Maths::AccCumNorm(-l_d1);
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
                return DigitalPrice(forward, strike, 0.0, maturity, rate, Finance::Payoff::STRADDLE);
            }
            else
            {
                const double volatility = volSmile(strike);
                double noSmiledPrice = 0.0;
                if (optionType == Finance::Payoff::CALL)
                {
                    const double l_d2 = d2(forward, strike, volatility, maturity);
                    noSmiledPrice = exp(-rate * maturity) * Maths::AccCumNorm(l_d2);
                }
                else // put
                {
                    const double l_d1 = d1(forward, strike, volatility, maturity);
                    noSmiledPrice = exp(-rate * maturity) * Maths::AccCumNorm(-l_d1);
                }
                return noSmiledPrice - volSmile.skew(strike) * VegaVanillaOption(forward, strike, volatility, maturity, rate, optionType);
            }
        }
        
        double Analytic::d2CdStrike2(double forward,
                                     double strike,
                                     double volatility,
                                     double maturity,
                                     double rate,
                                     Finance::Payoff::VanillaOptionType optionType) const
        {
            if (optionType == Finance::Payoff::STRADDLE)
            {
                //  Digital straddle pays 1, so is equal to zero-coupon bond
                std::cout << "Straddle case = Zero coupon bond : paying one unit of domestic currency at maturity" << std::endl;
                return 0;
            }
            else if (optionType == Finance::Payoff::CALL)
            {
                const double l_d2 = d2(forward, strike, volatility, maturity);
                return -1.0 / (strike * volatility * sqrt(maturity)) * exp(-0.5 * l_d2 * l_d2) * ONE_OVER_SQUARE_ROOT_OF_2_PI;
            }
            else // put
            {
                const double l_d1 = d1(forward, strike, volatility, maturity);
                return 1.0 / (strike * volatility * sqrt(maturity)) * exp(-0.5 * l_d1 * l_d1) * ONE_OVER_SQUARE_ROOT_OF_2_PI;
            }
        }
        
        void Analytic::CheckPastFixings(const std::vector<std::pair<double, double> > &pastFixings) const
        {
            for (std::vector<std::pair<double, double> >::const_iterator pastFixing = pastFixings.begin() ; pastFixing != pastFixings.end() ; ++pastFixing)
            {
                if (pastFixing->first > 0.0)
                {
                    throw EXCEPTION("Time for past fixing not negative");
                }
                if (pastFixing->second <= 0.0)
                {
                    throw EXCEPTION("Past fixing is negative");
                }
            }
        }
        
        double Analytic::AsianOption(double spot,
                                     double strike,
                                     Finance::Payoff::VanillaOptionType optionType,
                                     double volatility,
                                     double maturity,
                                     double rate,
                                     const std::vector<double> & futureObservationTimes,
                                     const std::vector<std::pair<double, double> > & pastFixings) const
        {
            //  Check if final observation times is before maturity
            if (futureObservationTimes.back() > maturity)
            {
                throw EXCEPTION("Final observation times is after maturity");
            }
            //  Moment matching method to get the price
            const std::size_t totalObservationsTimes = futureObservationTimes.size() + pastFixings.size();
            
            //  Compute the forward
            double forward = 0.0;
            for (std::size_t i = 0 ; i < pastFixings.size() ; ++i)
            {
                forward += pastFixings.at(i).second;
            }
            for (std::size_t i = 0 ; i < futureObservationTimes.size() ; ++i)
            {
                forward += spot * exp(rate * futureObservationTimes.at(i));
            }
            forward /= totalObservationsTimes;
            
            //  compute the variance
            //  Computation based on following paper : Analytical formula for Asian option Alexandre Humeau (6th April 2014)
            double denominator = 0.0, numerator = 0.0;
            for (size_t i = 0 ; i < futureObservationTimes.size() ; ++i)
            {
                denominator += exp(rate * futureObservationTimes.at(i));
                for (size_t j = 0 ; j < futureObservationTimes.size() ; ++j)
                {
                    numerator += exp(rate * (futureObservationTimes.at(i) + futureObservationTimes.at(j))) * (exp(volatility * volatility * std::min(futureObservationTimes.at(i), futureObservationTimes.at(j))) - 1.0);
                }
            }
            denominator /= futureObservationTimes.size();
            denominator *= denominator;
            numerator /= (futureObservationTimes.size() * futureObservationTimes.size());
            
            //const double volatilityaverage = log (variance / forward / forward) / maturity;
            const double volatilityaverage = sqrt(log(1 + numerator / denominator) / maturity);
            return VanillaPrice(forward, strike, volatilityaverage, maturity, rate, optionType);
        }
    }
}