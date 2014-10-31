//
//  Bond.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 25/05/13.
//
//

#ifndef __CVATools__Bond__
#define __CVATools__Bond__

#include <iostream>
#include "Coupon.h"
#include "Frequency.h"

namespace Finance
{
    namespace Instruments
    {
        class Bond
        {
        protected:
            std::vector<Base::Coupon> vCoupons_;
            bool bIsNotionalRepaidBack_;
            double dNotional_;
            void Create(//  Inputs
                        const std::vector<double> & dCoupons,
                        const Utilities::Date::MyDate & sStart,
                        const Utilities::Date::MyDate & sEnd,
                        Finance::Base::MyBasis eBasis,
                        Finance::Base::MyFrequency eFrequency,
                        bool bIsFixedRate,
                        //  Output
                        std::vector<Base::Coupon> & vCoupons);
        public:
            Bond(double dNotional, bool bIsNotionalRepaidBack);
            Bond(double dNotional, bool bIsNotionalRepaidBack, const std::vector<Base::Coupon> & vCoupons);
        };
    }
}

#endif /* defined(__CVATools__Bond__) */
