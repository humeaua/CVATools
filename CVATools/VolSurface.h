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
#include "VolSmile.h"

namespace Finance
{
    namespace Volatility
    {
        class VolatilitySurface
        {
        protected:
            std::vector<VolSmile> m_VolSurface;
            std::vector<double> m_Expiries;
            
            double m_Spot;
            
        private:
            
            virtual bool CheckButterflySpreadArbitrage() const;
            virtual bool CheckCalendarSpreadArbitrage() const;
            
        public:
            VolatilitySurface(const std::vector<VolSmile> & VolSurface, const double & Spot);
            
            virtual double operator()(const double & Expiry, const double & Strike) const;
            virtual VolSmile GetSmile(const double & Expiry) const;
            
            virtual bool IsArbitrageFree() const;
        };
    }
}

#endif /* defined(__CVATools__VolSurface__) */
