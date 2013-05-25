//
//  Coupon.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 25/05/13.
//
//

#include "Coupon.h"

Coupon::Coupon(double dCoupon,
               bool bIsFixedRate,
               const Utilities::Date::MyDate & sStart,
               const Utilities::Date::MyDate & sEnd,
               Finance::MyBasis eBasis) :
dCoupon_(dCoupon),
bIsFixedRate_(bIsFixedRate),
Finance::EventOfSchedule(sStart, sEnd, eBasis)

{}

Coupon::~Coupon()
{}

double Coupon::GetCoupon() const
{
    return dCoupon_;
}

bool Coupon::IsFixedRateCoupon() const
{
    return bIsFixedRate_;
}