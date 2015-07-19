//
//  Coupon.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 25/05/13.
//
//

#include "Coupon.h"
#include "DateShifter.h"

namespace Finance
{
    namespace Base
    {
        Coupon::Coupon(double dCoupon,
                       bool bIsFixedRate,
                       const Utilities::Date::MyDate & sStart,
                       const Utilities::Date::MyDate & sEnd,
                       Finance::Base::MyBasis eBasis,
                       const Utilities::HolidaysPtr & holidays) :
        dCoupon_(dCoupon),
        bIsFixedRate_(bIsFixedRate),
        Finance::Base::EventOfSchedule(sStart, sEnd, eBasis, DateShifter_Ptr(new DateShifterSimple(0, Utilities::Date::DAY, holidays)))
        
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