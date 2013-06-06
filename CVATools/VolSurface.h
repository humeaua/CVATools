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
#include <map>

class VolatilitySurface
{
protected:
    //    Expiry in days    Strike  Volatility
    std::map<long, std::map<double, double> > VolSurface_;
    
    
public:
    VolatilitySurface(const std::map<long, std::map<double, double> > VolSurface);
    virtual ~VolatilitySurface();

    virtual double Get(long lExpiry, double dStrike) const;
};

#endif /* defined(__CVATools__VolSurface__) */
