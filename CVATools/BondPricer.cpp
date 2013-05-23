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

BondPricer::BondPricer(const Utilities::Date::MyDate & sStart, const Utilities::Date::MyDate & sEnd, const Finance::YieldCurve & sYieldCurve, Finance::MyBasis eBasis, Finance::MyFrequency eFrequency, const DVector & dCoupons, double dNotional, bool bIsFixedRate, double dTolerance, std::size_t iNIterMax) : Finance::Schedule(sStart, sEnd, sYieldCurve, eBasis, eFrequency), dCoupons_(dCoupons), dNotional_(dNotional), bIsFixedRate_(bIsFixedRate), sStart_(sStart), sYieldCurve_(sYieldCurve), dToleranceNewton_(dTolerance), iNIterMaxNewton_(iNIterMax)
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
    //  Initialization of Today Date
    std::time_t lToday;
    std::tm *stm;
    time(&lToday);
    
    stm = localtime(&lToday);
    Utilities::Date::MyDate sTodayDate(*stm);
    
    double dPrice = 0.;
    if (bIsFixedRate_)
    {
        for (std::size_t iDate = 0 ; iDate < dCoupons_.size() ; ++iDate)
        {
            if (sSchedule_[iDate].GetEndDate() > sTodayDate)
            {
                dPrice += dCoupons_[iDate] * sSchedule_[iDate].GetPayingDateDF() * sSchedule_[iDate].GetCoverage();
            }
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
            if (sSchedule_[iDate].GetEndDate() > sTodayDate)
            {
                dPrice += dCoupons_[iDate] * (sSchedule_[iDate - 1].GetPayingDateDF() - sSchedule_[iDate].GetPayingDateDF());
            }
        }
        dPrice += dNotional_ * sSchedule_.back().GetPayingDateDF();
    }
    return dPrice;
}

bool BondPricer::HasAlreadyBegun() const
{
    //  Initialization of Today Date
    std::time_t lToday;
    std::tm *stm;
    time(&lToday);
    
    stm = localtime(&lToday);
    static Utilities::Date::MyDate sTodayDate(*stm);
    
    return sStart_ < sTodayDate;
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
    for (std::size_t iDate = 0 ; iDate < dCoupons_.size() ; ++iDate)
    {
        dDeriv -= dCoverageFromToday_[iDate] * dCoupons_[iDate] * pow(1. + r, - dCoverageFromToday_[iDate] - 1);
    }
    dDeriv -= dCoverageFromToday_.back() * pow(1. + r, - dCoverageFromToday_.back() - 1);
    return dDeriv;
}

double BondPricer::PriceToYieldFunc(double r) const
{
    double dPrice = 0.0;
    for (std::size_t iDate = 0 ; iDate < dCoupons_.size() ; ++iDate)
    {
        dPrice += dCoupons_[iDate] * pow(1. + r, - dCoverageFromToday_[iDate]);
    }
    dPrice += pow(1. + r, - dCoverageFromToday_.back());
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