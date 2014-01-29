//
//  SVIParameters.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 17/06/13.
//
//

#include "SVIParameters.h"
#include <cmath>
#include "InterExtrapolation.h"
#include <numeric>

namespace Finance
{
    namespace Volatility
    {
        SVIParameters::SVIParameters(double dSpot) : dSpot_(dSpot)
        {}
        
        double SVIParameters::Volatility(double k, double t) const
        {
            // interpolate linearly the factors in time
            //Utilities::Interp::InterExtrapolationType eInterpType = Utilities::Interp::LIN;
            //Utilities::Interp::InterExtrapolation1D sInterpA(dExpiries_, dA_, eInterpType), sInterpB(dExpiries_, dB_, eInterpType), sInterpRho(dExpiries_, dRho_, eInterpType), sInterpM(dExpiries_, dM_, eInterpType), sInterpSigma(dExpiries_, dSigma_, eInterpType);
            Utilities::Interp::LinearInterpolator sInterpA(dExpiries_, dA_), sInterpB(dExpiries_, dB_), sInterpRho(dExpiries_, dRho_), sInterpM(dExpiries_, dM_), sInterpSigma(dExpiries_, dSigma_);
            
            double dA = sInterpA(t), dB = sInterpB(t), dRho = sInterpRho(t), dM = sInterpM(t), dSigma = sInterpSigma(t);
            
            return sqrt(dA + dB * (dRho * (k - dM) + sqrt((k - dM) * (k - dM) + dSigma * dSigma)));
        }
        
        double SVIParameters::Variance(double k, double t) const
        {
            double dVol = Volatility(k,t);
            return dVol * dVol * t;
        }
        
        void SVIParameters::Calibrate(const std::map<long, std::map<double, double> > &sVolSurface)
        {
            //  first add expiries in the vector
            for (std::map<long, std::map<double, double> >::const_iterator it = sVolSurface.begin() ; it != sVolSurface.end(); ++it)
            {
                dExpiries_.push_back(it->first);
            }
            // to be implemented
            // loop over the expiries
            
            for (std::vector<double>::iterator itExpiry = dExpiries_.begin() ; itExpiry != dExpiries_.end() ; ++itExpiry)
            {
                std::vector<double> dStrikes, dVols;
                FillStrikesAndVols(sVolSurface, *itExpiry, dStrikes, dVols);
                
                //  minimisation of the volatility square function w.r.t. the SVI parameters
                
                // (a,b,rho,m,sigma) = argmin sum_i=1^n (vol^2 - a - b(rho(k-m) + sqrt((k-m)^2 + sigma^2)))
                
                // see http://www.zeliade.com/whitepapers/zwp-0005.pdf for an example of implementation method
                
                //  1st step : find \nabla f = 0 everywhere
                //  if minimum \in domain (arbitrage free domain) then OK
                //  Else look for minimum in border of domain
                
                //  We need at least the volatility to be quoted on 3 strikes (see above paper)
            }
        }
        
        void SVIParameters::FillStrikesAndVols(// inputs
                                               const std::map<long, std::map<double, double> > & sVolSurface,
                                               long lExpiry,
                                               //outputs
                                               std::vector<double> & dStrikes,
                                               std::vector<double> & dVols) const
        {
            if (sVolSurface.count(lExpiry))
            {
                std::map<double, double> sVolSmile = sVolSurface.find(lExpiry)->second;
                for (std::map<double, double>::iterator itStrike = sVolSmile.begin() ; itStrike != sVolSmile.end() ; ++itStrike)
                {
                    dStrikes.push_back(log(itStrike->first / dSpot_));
                    dVols.push_back(itStrike->second);
                }
            }
        }
    }
}