//
//  VolSurface.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 06/06/13.
//
//

#include "VolSurface.h"
#include <stdexcept>
#include "InterExtrapolation.h"
#include <cmath>
#include <stdexcept>

namespace Finance
{
    namespace Volatility
    {
        VolatilitySurface::VolatilitySurface(double dSpot, const std::map<long, std::map<double, double> > VolSurface) : dSpot_(dSpot), VolSurface_(VolSurface)
        {
            if (dSpot > 0.0)
            {
                Calibrate(VolSurface_);
            }
            else
            {
                throw std::runtime_error("VolatilitySurface::VolatilitySurface : Spot is negative");
            }
        }
        
        VolatilitySurface::~VolatilitySurface()
        {
            for (std::map<long, std::map<double, double> >::iterator it = VolSurface_.begin() ; it != VolSurface_.end() ; ++it)
            {
                it->second.clear();
            }
            VolSurface_.clear();
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
                    throw std::runtime_error("Strike not found");
                }
            }
            else
            {
                throw std::runtime_error("Expiry not found");
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
                throw std::runtime_error("VolatilitySurface::Interpolate : Strike is negative");
            }
        }
    }
}