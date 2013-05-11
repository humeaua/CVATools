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

BondPricer::BondPricer(const Utilities::Date::MyDate & sStart, const Utilities::Date::MyDate & sEnd, const Finance::YieldCurve & sYieldCurve, Finance::MyBasis eBasis, Finance::MyFrequency eFrequency, const DVector & dCoupons, double dNotional, bool bIsFixedRate) : Finance::Schedule(sStart, sEnd, sYieldCurve, eBasis, eFrequency), dCoupons_(dCoupons), dNotional_(dNotional), bIsFixedRate_(bIsFixedRate), sStart_(sStart), sYieldCurve_(sYieldCurve)
{
    Utilities::require(dCoupons_.size() == sSchedule_.size(), "Coupon and Schedule do not have the same size");
}

BondPricer::~BondPricer()
{
    sSchedule_.clear();
    dCoupons_.clear();
}

double BondPricer::Price() const
{
    double dPrice = 0.;
    if (bIsFixedRate_)
    {
        for (std::size_t iDate = 0 ; iDate < dCoupons_.size() ; ++iDate)
        {
            dPrice += dCoupons_[iDate] * sSchedule_[iDate].GetPayingDateDF() * sSchedule_[iDate].GetCoverage();
        }
        dPrice += dNotional_ * sSchedule_.back().GetPayingDateDF();
    }
    else
    {
        //  The coupons are seen as notional of libor described in the payoff
        Finance::DF sDF(sYieldCurve_);
        dPrice += dCoupons_[0] * (sDF.DiscountFactor(sStart_) - sSchedule_[0].GetPayingDateDF());
        for (std::size_t iDate = 1 ; iDate < dCoupons_.size() ; ++iDate)
        {
            dPrice += dCoupons_[iDate] * (sSchedule_[iDate - 1].GetPayingDateDF() - sSchedule_[iDate].GetPayingDateDF());
        }
        dPrice += dNotional_ * sSchedule_.back().GetPayingDateDF();
    }
    return dPrice;
}