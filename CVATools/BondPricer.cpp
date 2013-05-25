//
//  BondPricer.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 11/05/13.
//
//

#include "BondPricer.h"
#include "Require.h"
#include "DiscountFactor.h"
#include <cmath>
#include "Coverage.h"

BondPricer::BondPricer(const Utilities::Date::MyDate & sStart, const Utilities::Date::MyDate & sEnd, const Finance::YieldCurve & sYieldCurve, Finance::MyBasis eBasis, Finance::MyFrequency eFrequency, const DVector & dCoupons, double dNotional, bool bIsFixedRate, double dTolerance, std::size_t iNIterMax) : sYieldCurve_(sYieldCurve), dToleranceNewton_(dTolerance), iNIterMaxNewton_(iNIterMax), Bond(dNotional, true)
{
    CreateBond(dCoupons, sStart, sEnd, eBasis, eFrequency, bIsFixedRate, vCoupons_);
}

BondPricer::~BondPricer()
{}

double BondPricer::Price() const
{
    //  Initialization of Today Date
    Utilities::Date::MyDate sTodayDate = Utilities::Date::InitializeTodayDate();
    
    double dPrice = 0.;
    if (vCoupons_.size() > 0)
    {
        //  1st coupon
        if (vCoupons_[0].IsFixedRateCoupon())
        {
            dPrice += vCoupons_[0].GetCoupon() * vCoupons_[0].GetPayingDateDF(sYieldCurve_);
        }
        else
        {
            Finance::DF sDF(sYieldCurve_);
            dPrice += vCoupons_[0].GetCoupon() * (sDF.DiscountFactor(sTodayDate) - vCoupons_[0].GetPayingDateDF(sYieldCurve_));
        }
        for (std::size_t iDate = 1 ; iDate < vCoupons_.size() ; ++iDate)
        {
            if (vCoupons_[iDate].IsFixedRateCoupon())
            {
                dPrice += vCoupons_[iDate].GetCoupon() * vCoupons_[iDate].GetPayingDateDF(sYieldCurve_);
            }
            else
            {
                dPrice += vCoupons_[iDate].GetCoupon() * (vCoupons_[iDate - 1].GetPayingDateDF(sYieldCurve_) - vCoupons_[iDate].GetPayingDateDF(sYieldCurve_));
            }
        }
        if (bIsNotionalRepaidBack_)
        {
            dPrice += dNotional_ * vCoupons_.back().GetPayingDateDF(sYieldCurve_);
        }
    }
    return dPrice;
}

bool BondPricer::HasAlreadyBegun() const
{
    //  Initialization of Today Date
    Utilities::Date::MyDate sTodayDate = Utilities::Date::InitializeTodayDate();
    
    return vCoupons_.front().GetStartDate() < sTodayDate;
}

double BondPricer::CleanPrice() const
{
    //  to be implemented
    return 0.0;
}

double BondPricer::DirtyPrice() const
{
    //  to be implemented
    return 0.0;
}

double BondPricer::PriceToYieldDeriv(double r) const
{
    double dDeriv = 0.0;
    Utilities::Date::MyDate sToday = Utilities::Date::InitializeTodayDate();
    for (std::size_t iDate = 0 ; iDate < vCoupons_.size() ; ++iDate)
    {
        double dCoverage = GetCoverage(sToday, vCoupons_[iDate].GetEndDate(), vCoupons_[iDate].GetBasis());
        dDeriv -= dCoverage * vCoupons_[iDate].GetCoupon() * pow(1. + r, - dCoverage - 1);
    }
    double dCoverage = GetCoverage(sToday, vCoupons_.back().GetEndDate(), vCoupons_.back().GetBasis());
    dDeriv -= dCoverage * pow(1. + r, - dCoverage - 1);
    return dDeriv;
}

double BondPricer::PriceToYieldFunc(double r) const
{
    double dPrice = 0.0;
    Utilities::Date::MyDate sToday = Utilities::Date::InitializeTodayDate();
    for (std::size_t iDate = 0 ; iDate < vCoupons_.size() ; ++iDate)
    {
        dPrice += vCoupons_[iDate].GetCoupon() * pow(1. + r, - GetCoverage(sToday, vCoupons_[iDate].GetEndDate(), vCoupons_[iDate].GetBasis()));
    }
    dPrice += pow(1. + r, - GetCoverage(sToday, vCoupons_.back().GetEndDate(), vCoupons_.back().GetBasis()));
    return dPrice;
}

double BondPricer::PriceToYield(double dPrice) const
{
    //  Newton Raphson method to find the yield that correspond to the price of the bond
    double dYield = 0.0;
    std::size_t iNIter = 0;
    
    double dPrice0 = PriceToYieldFunc(dYield);
    
    while (std::abs(dPrice0 - dPrice) > dToleranceNewton_ && iNIter <= iNIterMaxNewton_)
    {
        dYield -= (dPrice0 - dPrice) / PriceToYieldDeriv(dYield);
        dPrice0 = PriceToYieldFunc(dYield);
        
        //  Update number of iterations
        iNIter++;
    }
    
    return dYield;
}

double BondPricer::I_Spread(double dPrice) const
{
    Utilities::Date::MyDate sTodayDate = Utilities::Date::InitializeTodayDate();
    return PriceToYield(dPrice) - sYieldCurve_.Interp1D(vCoupons_.back().GetEndDate().Diff(sTodayDate));
}