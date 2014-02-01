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
        class VolSmile : public Utilities::Interp::HermiteSplineCubicInterpolator
        {
        protected:
            double dFwdRef_;
            double dMaturity_;
            
            virtual double CallPrice(double K) const;
            virtual bool CheckButterflySpreadArbitrage() const;
        public:
            VolSmile(const std::vector<double> & dStrikes, const std::vector<double> & dVols, double dFwdRef, double T);
            
            virtual bool IsArbitrageFree() const;
            
            virtual double GetFirstStrike() const;
            virtual double GetLastStrike() const;
            virtual double GetMeanStrike() const;
            virtual double GetStdDevStrike() const; // TEST : to get the parameter sigma in SVI ?
        };
    }
}

#endif /* defined(__CVATools__VolSmile__) */
