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
        VolatilitySurface::VolatilitySurface(const std::vector<VolSmile> & VolSurface) : m_VolSurface(VolSurface)
        {
            for (std::vector<VolSmile>::const_iterator volSmile = m_VolSurface.begin() ; volSmile != m_VolSurface.end() ; ++volSmile)
            {
                m_Expiries.push_back(volSmile->Maturity());
            }
        }
        
        double VolatilitySurface::operator()(double Expiry, double Strike) const
        {
            std::size_t iExpiry = 0;
            if (Utilities::IsFound(m_Expiries, Expiry, iExpiry))
            {
                return m_VolSurface[iExpiry](Strike);
            }
            else
            {
                /*//  Linear interpolation of the variance, spline cubic over the log strike
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
                    throw EXCEPTION("Not yet implemented");
                }
                else
                {
                    //  Extrapolation Error ?
                    throw EXCEPTION("Index not found in Volatility surface");
                }*/
                throw EXCEPTION("Not yet implemented");
            }
        }
        
        bool VolatilitySurface::IsArbitrageFree() const
        {
            return CheckButterflySpreadArbitrage() && CheckCalendarSpreadArbitrage();
        }
        
        bool VolatilitySurface::CheckButterflySpreadArbitrage() const
        {
            //  Call price convex function of strike for all expiries
            for (std::vector<VolSmile>::const_iterator volSmile = m_VolSurface.begin() ; volSmile != m_VolSurface.end() ; ++volSmile)
            {
                if (!volSmile->IsArbitrageFree())
                {
                    return false;
                }
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