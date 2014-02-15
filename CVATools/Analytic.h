//
//  Analytic.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 15/02/14.
//
//

#ifndef __CVATools__Analytic__
#define __CVATools__Analytic__

#include <iostream>
#include "VanillaOptionType.h"
#include "VolSmile.h"

namespace Finance
{
    namespace Pricers
    {
        class Analytic
        {
        private:
            virtual double d1(double forward, double strike, double volatility, double maturity) const;
            virtual double d2(double forward, double strike, double volatility, double maturity) const;
            virtual void CheckParameters() const;
        public:
            virtual double VanillaPrice(double forward, double strike, double volatility, double maturity, double rate, Finance::Payoff::VanillaOptionType optionType) const;
            virtual double VegaVanillaOption(double forward, double strike, double volatility, double maturity, double rate, Finance::Payoff::VanillaOptionType optionType) const;
            virtual double DigitalPrice(double forward, double strike, double volatility, double maturity, double rate, Finance::Payoff::VanillaOptionType optionType) const;
            virtual double DigitalPrice(double forward, double strike, const Finance::Volatility::VolSmile & volSmile, double maturity, double rate, Finance::Payoff::VanillaOptionType optionType) const;
        };
    }
}

#endif /* defined(__CVATools__Analytic__) */
