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
#include "Exception.h"

namespace Finance
{
    namespace Volatility
    {
        VolatilitySurface::VolatilitySurface(const std::vector<VolSmile> & VolSurface, const double & Spot) : m_VolSurface(VolSurface), m_Spot(Spot)
        {
            for (std::vector<VolSmile>::const_iterator volSmile = m_VolSurface.begin() ; volSmile != m_VolSurface.end() ; ++volSmile)
            {
                m_Expiries.push_back(volSmile->Maturity());
            }
        }
        
        double VolatilitySurface::operator()(const double & Expiry, const double & Strike) const
        {
            int iExpiry = 0;
            if (Utilities::IsFound(m_Expiries, Expiry, iExpiry))
            {
                return m_VolSurface[iExpiry](Strike);
            }
            else
            {
                return GetSmile(Expiry).operator()(Strike);
            }
        }
        
        VolSmile VolatilitySurface::GetSmile(const double &Expiry) const
        {
            //  Linear interpolation of the variance, spline cubic over the log strike
            int iIndex = Utilities::FindInVector(m_Expiries, Expiry);
            
            if (iIndex != -1 && iIndex < m_Expiries.size() - 1)
            {
                //  lExpiry is between lExpiries[iIndex] and lExpiries[iIndex + 1]
                const VolSmile & VolSmile0 = m_VolSurface[iIndex];
                
                const VolSmile & VolSmile1 = m_VolSurface[iIndex + 1];
                
                REQUIREEXCEPTION(VolSmile0.size() == VolSmile1.size(), "Vol Smiles are not the same size");
                
                std::vector<double> dStrikes;
                std::vector<std::pair<double, double> > StrikesAndVols;
                const std::vector<double> logStrikes0 = VolSmile0.LogStrikes(), logStrikes1 = VolSmile1.LogStrikes(), Volatilities0 = VolSmile0.Volatilities(), Volatilities1 = VolSmile1.Volatilities();
                
                const double Expiry0 = m_Expiries[iIndex], Expiry1 = m_Expiries[iIndex + 1];
                //  Linear interpolation of the low of the forward ref, should be ok for now
                const double NewForwardRef = exp((log(VolSmile0.FwdRef()) * (Expiry - Expiry0) + log(VolSmile1.FwdRef()) * (Expiry - Expiry1)) / (Expiry0 - Expiry1));
                
                // Build the strike vector
                std::vector<double>::const_iterator oldStrike = logStrikes0.begin();
                for ( ; oldStrike != logStrikes0.end() ; ++oldStrike)
                {
                    dStrikes.push_back(*oldStrike + log(VolSmile0.FwdRef() / NewForwardRef));
                }
                oldStrike = logStrikes1.begin();
                for ( ; oldStrike != logStrikes1.end() ; ++oldStrike)
                {
                    dStrikes.push_back(*oldStrike + log(VolSmile1.FwdRef() / NewForwardRef));
                }
                
                // Interpolate linearly in variance : check for arbitrage free conditions
                // I think the smile I build is arbitrable
                for (std::size_t i = 0 ; i < dStrikes.size() ; ++i)
                {
                    const double dVol0 = VolSmile0(dStrikes[i]), dVol1 = VolSmile1(dStrikes[i]);
                    double dVol = dVol0 * dVol0 * (Expiry - Expiry0) + dVol1 * dVol1 * (Expiry - Expiry1);
                    dVol /= Expiry0 - Expiry1;
                    
                    if (dVol < 0.0)
                    {
                        // Build error message just in case
                        std::stringstream Expiry, Strike;
                        Expiry << Expiry;
                        Strike << dStrikes[i];
                        
                        
                        throw EXCEPTION("Volatility is negative : Expiry : " + Expiry.str() + " Strike : " + Strike.str());
                    }
                    StrikesAndVols.push_back(std::make_pair(dStrikes[i], dVol));
                }
                
                //  Sort the vector of pair as we pushed back the first smile then the second (think of a better solution by comparing the moneyness directly if too slow)
                std::sort(StrikesAndVols.begin(), StrikesAndVols.end(), Utilities::Pair1stLowerOrEqual);
                
                //  Add vol in the vector
                std::vector<double> dVols(StrikesAndVols.size());
                for (std::size_t i = 0 ; i < StrikesAndVols.size() ; ++i)
                {
                    dVols[i] = StrikesAndVols[i].second;
                }
                
                return VolSmile(dStrikes, dVols, NewForwardRef, Expiry);
            }
            else
            {
                //  Extrapolation Error ?
                throw EXCEPTION("Index not found in Volatility surface");
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