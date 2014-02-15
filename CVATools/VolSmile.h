//
//  VolSmile.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 31/01/14.
//
//

#ifndef __CVATools__VolSmile__
#define __CVATools__VolSmile__

#include <iostream>
#include "InterExtrapolation.h"

namespace Finance
{
    namespace Volatility
    {
        class VolSmile : public Utilities::Interp::HermiteDegree5Interpolator
        {
        protected:
            double dFwdRef_;
            double dMaturity_;
            
            virtual double CallPrice(double K) const;
            virtual bool CheckButterflySpreadArbitrage() const;
        public:
            VolSmile(const std::vector<double> & dStrikes, const std::vector<double> & dVols, double dFwdRef, double T);
            
            virtual bool IsArbitrageFree() const;
            
            //  Getters
            virtual double FwdRef() const;
            virtual double Maturity() const;
            virtual std::vector<double> LogStrikes() const;
            virtual std::vector<double> Volatilities() const;
            
            virtual double GetFirstStrike() const;
            virtual double GetLastStrike() const;
            virtual double GetMeanStrike() const;
            virtual double GetStdDevStrike() const; // TEST : to get the parameter sigma in SVI ?
            
            virtual bool IsATMVolQuoted() const;
            
            //  to get the volatility
            virtual double operator()(double strike) const;
            
            //  to get the skew
            virtual double skew(double strike) const;
        };
    }
}

#endif /* defined(__CVATools__VolSmile__) */
