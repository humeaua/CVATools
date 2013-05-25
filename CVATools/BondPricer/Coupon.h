//
//  Coupon.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 25/05/13.
//
//

#ifndef __CVATools__Coupon__
#define __CVATools__Coupon__

#include <iostream>
#include "EventOfSchedule.h"

class Coupon : public Finance::EventOfSchedule
{
protected:
    double dCoupon_;
    bool bIsFixedRate_;
    
public:
    Coupon(double dCoupon, bool bIsFixedRate, const Utilities::Date::MyDate & sStart, const Utilities::Date::MyDate & sEnd, Finance::MyBasis eBasis);
    virtual ~Coupon();
    
    double GetCoupon() const;
    bool IsFixedRateCoupon() const;
};

#endif /* defined(__CVATools__Coupon__) */
