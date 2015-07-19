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
#include "IHolidays.h"

namespace Finance
{
    namespace Instruments
    {
        class Bond
        {
        protected:
            std::vector<std::tr1::shared_ptr<Base::Coupon> > vCoupons_;
            bool bIsNotionalRepaidBack_;
            double dNotional_;
            Utilities::HolidaysPtr m_holidays;
            void Create(//  Inputs
                        const std::vector<double> & dCoupons,
                        const Utilities::Date::MyDate & sStart,
                        const Utilities::Date::MyDate & sEnd,
                        Finance::Base::MyBasis eBasis,
                        Finance::Base::MyFrequency eFrequency,
                        bool bIsFixedRate,
                        const Utilities::HolidaysPtr & holidays,
                        //  Output
                        std::vector<std::tr1::shared_ptr<Base::Coupon> > & vCoupons);
        public:
            Bond(double dNotional, bool bIsNotionalRepaidBack);
            Bond(double dNotional, bool bIsNotionalRepaidBack, const std::vector<std::tr1::shared_ptr<Base::Coupon> > & vCoupons);
        };
    }
}

#endif /* defined(__CVATools__Bond__) */
