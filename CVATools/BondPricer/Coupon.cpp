//
//  Coupon.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 25/05/13.
//
//

#include "Coupon.h"

namespace Finance
{
    namespace Base
    {
        Coupon::Coupon(double dCoupon,
                       bool bIsFixedRate,
                       const Utilities::Date::MyDate & sStart,
                       const Utilities::Date::MyDate & sEnd,
                       Finance::Base::MyBasis eBasis) :
        dCoupon_(dCoupon),
        bIsFixedRate_(bIsFixedRate),
        Finance::Base::EventOfSchedule(sStart, sEnd, eBasis)
        
        {}
        
        double Coupon::GetCoupon() const
        {
            return dCoupon_;
        }
        
        bool Coupon::IsFixedRateCoupon() const
        {
            return bIsFixedRate_;
        }
    }
}