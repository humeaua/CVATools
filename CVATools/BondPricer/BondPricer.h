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

class BondPricer : public Finance::Schedule {
protected:
    DVector dCoupons_;
    double dNotional_;
    bool bIsFixedRate_;
    
    Utilities::Date::MyDate sStart_;
    Finance::YieldCurve sYieldCurve_;
    
public:
    BondPricer(const Utilities::Date::MyDate & sStart, const Utilities::Date::MyDate & sEnd, const Finance::YieldCurve & sYieldCurve, Finance::MyBasis eBasis, Finance::MyFrequency eFrequency, const DVector & dCoupons, double dNotional, bool bIsFixedRate);
    virtual ~BondPricer();
    
    virtual double Price() const;
};

#endif
