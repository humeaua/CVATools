//
//  VolSurface.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 06/06/13.
//
//

#ifndef __CVATools__VolSurface__
#define __CVATools__VolSurface__

#include <iostream>
#include "SVIParameters.h"

namespace Finance
{
    namespace Volatility
    {
        class VolatilitySurface : public SVIParameters
        {
        protected:
            //    Expiry in days    Strike  Volatility
            std::map<long, std::map<double, double> > VolSurface_;
            
        private:
            virtual double Get(long lExpiry, double dStrike) const;
            
            virtual bool CheckButterflySpreadArbitrage() const;
            virtual bool CheckCalendarSpreadArbitrage() const;
            
        public:
            VolatilitySurface(double dSpot, const std::map<long, std::map<double, double> >& VolSurface);
            virtual double Interpolate(long lExpiry, double dStrike) const;
            
            virtual bool IsArbitrageFree() const;
        };
    }
}

#endif /* defined(__CVATools__VolSurface__) */
