//
//  Bond.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 25/05/13.
//
//

#include "Bond.h"
#include "Schedule.h"
#include "Require.h"

void CreateBond(//  Inputs
                const std::vector<double> & dCoupons,
                const Utilities::Date::MyDate & sStart,
                const Utilities::Date::MyDate & sEnd,
                Finance::MyBasis eBasis,
                Finance::MyFrequency eFrequency,
                bool bIsFixedRate,
                //  Output
                std::vector<Coupon> & vCoupons)
{
    Finance::Schedule sSchedule(sStart, sEnd, eBasis, eFrequency);
    
    std::vector<Finance::EventOfSchedule> vSchedule = sSchedule.GetSchedule();
    Utilities::require(vSchedule.size() == dCoupons.size(), "CreateBond : Coupon and Schedule do not have the same size. Cannot create Bond");
    
    for (std::size_t iDate = 0 ; iDate < vSchedule.size() ; ++iDate)
    {
        vCoupons.push_back(Coupon(dCoupons[iDate], bIsFixedRate, vSchedule[iDate].GetStartDate(), vSchedule[iDate].GetEndDate(), vSchedule[iDate].GetBasis()));
    }
}

Bond::Bond(double dNotional, bool bIsNotionalRepaidBack) : dNotional_(dNotional), bIsNotionalRepaidBack_(bIsNotionalRepaidBack)
{}

Bond::Bond(double dNotional, bool bIsNotionalRepaidBack, const std::vector<Coupon> & vCoupons) : bIsNotionalRepaidBack_(bIsNotionalRepaidBack), vCoupons_(vCoupons)
{}

Bond::~Bond()
{
    vCoupons_.clear();
}