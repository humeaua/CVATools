//
//  VolSurface.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 06/06/13.
//
//

#include "VolSurface.h"
#include "InterExtrapolation.h"
#include <cmath>
#include "Require.h"
#include "VectorUtilities.h"
#include <sstream>

namespace Finance
{
    namespace Volatility
    {
        VolatilitySurface::VolatilitySurface(double dSpot, const std::map<long, std::map<double, double> >&  VolSurface) : VolSurface_(VolSurface), Finance::Volatility::SVIParameters(dSpot)
        {
            REQUIREEXCEPTION(dSpot > 0.0, "Spot is negative");
            Calibrate(VolSurface_);
        }
        
        double VolatilitySurface::Get(long lExpiry, double dStrike) const
        {
            if (VolSurface_.count(lExpiry) != 0)
            {
                std::map<long, std::map<double, double> >::const_iterator it = VolSurface_.find(lExpiry);
                if (it->second.count(dStrike) != 0)
                {
                    return it->second.find(dStrike)->second;
                }
                else
                {
                    //  Spline cubic interpolation of log strike : good for now
                    const std::map<double,double> VolSmile = it->second;
                    std::map<double, double>::const_iterator iter0 = VolSmile.begin();
                    std::vector<double> dStrikes(VolSmile.size(), 0.0), dVols(VolSmile.size(), 0.0);
                    std::vector<double>::iterator iterVol = dVols.begin();
                    for (std::vector<double>::iterator iterStrike = dStrikes.begin() ; iterStrike != dStrikes.end() ; ++iterStrike, ++iter0, ++iterVol)
                    {
                        *iterStrike = log(iter0->first);
                        *iterVol = iter0->second;
                    }
                    
                    //Utilities::Interp::InterExtrapolation1D Interp(dStrikes, dVols, Utilities::Interp::HERMITE_SPLINE_CUBIC);
                    Utilities::Interp::HermiteSplineCubicInterpolator Interp(dStrikes, dVols);
                    return Interp(dStrike);
                }
            }
            else
            {
                //  Linear interpolation of the variance, spline cubic over the log strike
                std::vector<long> lExpiries(VolSurface_.size(), 0L);
                std::map<long, std::map<double, double> >::const_iterator it = VolSurface_.begin();
                for (std::size_t iExpiry = 0 ; iExpiry < VolSurface_.size() ; ++iExpiry, ++it)
                {
                    lExpiries[iExpiry] = it->first;
                }
                
                int iIndex = Utilities::FindInVector(lExpiries, lExpiry);
                
                if (iIndex != -1)
                {
                    //  lExpiry is between lExpiries[iIndex] and lExpiries[iIndex + 1]
                    const std::map<double,double> VolSmile0 = VolSurface_.find(lExpiries[iIndex])->second;
                    std::map<double, double>::const_iterator iter0 = VolSmile0.begin();
                    
                    const std::map<double, double> VolSmile1 = VolSurface_.find(lExpiries[iIndex])->second;
                    std::map<double, double>::const_iterator iter1 = VolSmile1.begin();
                    
                    REQUIREEXCEPTION(VolSmile0.size() == VolSmile1.size(), "Vol Smiles are not the same size");
                    
                    std::vector<double> dStrikes(VolSmile0.size(), 0.0), dVols(VolSmile0.size(), 0.0);
                    std::vector<double>::iterator iterVol = dVols.begin();
                    for (std::vector<double>::iterator iterStrike = dStrikes.begin() ; iterStrike != dStrikes.end() ; ++iterStrike, ++iter0, ++iterVol)
                    {
                        REQUIREEXCEPTION(iter0->first > 0.0, "Strike is negative");
                        *iterStrike = log(iter0->first / dSpot_);
                        *iterVol = iter0->second * iter0->second * (lExpiry - lExpiries[iIndex]) + iter1->second * iter1->second * (lExpiries[iIndex + 1] - lExpiry) ;
                        *iterVol /= (lExpiries[iIndex + 1] - lExpiries[iIndex]);
                        *iterVol *= lExpiry / 365.0; // ACT365FIXED day count convention
                        
                        // Build error message just in case
                        std::stringstream Expiry, Strike;
                        Expiry << lExpiry;
                        Strike << dSpot_ * exp(*iterStrike);
                        
                        REQUIREEXCEPTION(*iterVol >= 0.0, "Volatility is negative : Expiry : " + Expiry.str() + " Strike : " + Strike.str());
                    }
                    
                    //Utilities::Interp::InterExtrapolation1D Interp(dStrikes, dVols, Utilities::Interp::HERMITE_SPLINE_CUBIC);
                    Utilities::Interp::HermiteSplineCubicInterpolator Interp(dStrikes, dVols);
                    return sqrt(Interp(dStrike) * 365.0 / lExpiry); // return the volatility, not the variance
                }
                else
                {
                    //  Extrapolation Error ?
                    throw EXCEPTION("Index not found in Volatility surface");
                }
            }
        }
        
        double VolatilitySurface::Interpolate(long lExpiry, double dStrike) const
        {
            if (dStrike > 0.0)
            {
                return Volatility(log(dStrike / dSpot_), lExpiry / 365.0);
            }
            else
            {
                throw EXCEPTION("VolatilitySurface::Interpolate : Strike is negative");
            }
        }
        
        bool VolatilitySurface::IsArbitrageFree() const
        {
            return CheckButterflySpreadArbitrage() && CheckCalendarSpreadArbitrage();
        }
        
        bool VolatilitySurface::CheckButterflySpreadArbitrage() const
        {
            //  Call price convex function of strike for all expiries
            for (std::map<long, std::map<double, double> >::const_iterator itExpiry = VolSurface_.begin() ; itExpiry != VolSurface_.end() ; ++itExpiry)
            {
                
            }
            return true;
        }
        
        bool VolatilitySurface::CheckCalendarSpreadArbitrage() const
        {
            //  Variance increasing function of maturity
            return true;
        }
    }
}