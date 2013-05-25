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

void CreateBond(//  Inputs
                const std::vector<double> & dCoupons,
                const Utilities::Date::MyDate & sStart,
                const Utilities::Date::MyDate & sEnd,
                Finance::MyBasis eBasis,
                Finance::MyFrequency eFrequency,
                bool bIsFixedRate,
                //  Output
                std::vector<Coupon> & vCoupons);

class Bond {
protected:
    std::vector<Coupon> vCoupons_;
    bool bIsNotionalRepaidBack_;
    double dNotional_;
public:
    Bond(double dNotional, bool bIsNotionalRepaidBack);
    Bond(double dNotional, bool bIsNotionalRepaidBack, const std::vector<Coupon> & vCoupons);
    virtual ~Bond();
};

#endif /* defined(__CVATools__Bond__) */
