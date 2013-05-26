//
//  BondPricer.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 11/05/13.
//
//

#ifndef CVATools_BondPricer_h
#define CVATools_BondPricer_h

#include "Type.h"
#include "Schedule.h"
#include "Bond.h"

class BondPricer : public Bond{
protected:
    Finance::YieldCurve sYieldCurve_;
    
    //  Newton parameters
    double dToleranceNewton_;
    std::size_t iNIterMaxNewton_;
    
    virtual double PriceToYieldFunc(double r) const;
    virtual double PriceToYieldDeriv(double r) const;
    
    virtual double Z_SpreadFunc(double r) const;
    virtual double Z_SpreadDeriv(double r) const;
    
public:
    BondPricer(const Utilities::Date::MyDate & sStart, const Utilities::Date::MyDate & sEnd, const Finance::YieldCurve & sYieldCurve, Finance::MyBasis eBasis, Finance::MyFrequency eFrequency, const DVector & dCoupons, double dNotional, bool bIsFixedRate, double dToleranceNewton = 1e-06, std::size_t iNIterMaxNewton = 100);
    virtual ~BondPricer();
    
    virtual double Price() const;
    
    virtual bool HasAlreadyBegun() const;
    virtual double CleanPrice() const;
    virtual double DirtyPrice() const;
    
    //  Only for fixed coupon Bond
    virtual double PriceToYield(double dPrice) const;
    virtual double I_Spread(double dPrice) const;
    virtual double Z_Spread(double dPrice) const;
};

#endif
