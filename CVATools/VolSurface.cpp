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

namespace Finance
{
    namespace Volatility
    {
        VolatilitySurface::VolatilitySurface(double dSpot, const std::map<long, std::map<double, double> > VolSurface) : dSpot_(dSpot), VolSurface_(VolSurface), Finance::Volatility::SVIParameters(dSpot)
        {
            Utilities::requireException(dSpot > 0.0, "Spot is negative", "VolatilitySurface::VolatilitySurface");
            Calibrate(VolSurface_);
        }
        
        double VolatilitySurface::Get(long lExpiry, double dStrike) const
        {
            if (VolSurface_.count(lExpiry))
            {
                std::map<long, std::map<double, double> >::const_iterator it = VolSurface_.find(lExpiry);
                if (it->second.count(dStrike))
                {
                    return it->second.find(dStrike)->second;
                }
                else
                {
                    throw Utilities::MyException("VolatilitySurface::Get : Strike not found");
                }
            }
            else
            {
                throw Utilities::MyException("VolatilitySurface::Get : Expiry not found");
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
                throw Utilities::MyException("VolatilitySurface::Interpolate : Strike is negative");
            }
        }
    }
}