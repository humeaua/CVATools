//
//  BondPricer.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 11/05/13.
//
//

#include "BondPricer.h"
#include "DiscountFactor.h"
#include <cmath>
#include "Coverage.h"
#include "VectorUtilities.h"

namespace Finance
{
    namespace Pricers
    {
        PriceToYieldNewton::PriceToYieldNewton(const Bond & sBond, const Utilities::Date::MyDate & sToday, double dPrice, std::size_t iNIterMax, double dTolerance, double dEpsValueDeriv) : Bond(sBond), NewtonRaphson1D(iNIterMax, dTolerance, dEpsValueDeriv), dPrice_(dPrice), sToday_(sToday)
        {}
        
        PriceToYieldNewton::PriceToYieldNewton(const Bond & sBond, const Utilities::Date::MyDate & sToday, double dPrice) : dPrice_(dPrice), Bond(sBond), sToday_(sToday)
        {}
        
        double PriceToYieldNewton::f(double r) const
        {
            double dPrice = 0.0;
            for (std::size_t iDate = 0 ; iDate < vCoupons_.size() ; ++iDate)
            {
                dPrice += vCoupons_.at(iDate).GetCoupon() * pow(1. + r, - GetCoverage(sToday_, vCoupons_.at(iDate).GetEndDate(), vCoupons_[iDate].GetBasis()));
            }
            if (bIsNotionalRepaidBack_)
            {
                dPrice += pow(1. + r, - GetCoverage(sToday_, vCoupons_.back().GetEndDate(), vCoupons_.back().GetBasis()));
            }
            return dPrice - dPrice_;
        }
        
        double PriceToYieldNewton::df(double r) const
        {
            double dDeriv = 0.0;
            for (std::size_t iDate = 0 ; iDate < vCoupons_.size() ; ++iDate)
            {
                double dCoverage = GetCoverage(sToday_, vCoupons_.at(iDate).GetEndDate(), vCoupons_.at(iDate).GetBasis());
                dDeriv -= dCoverage * vCoupons_.at(iDate).GetCoupon() * pow(1. + r, - dCoverage - 1);
            }
            if (bIsNotionalRepaidBack_)
            {
                double dCoverage = GetCoverage(sToday_, vCoupons_.back().GetEndDate(), vCoupons_.back().GetBasis());
                dDeriv -= dCoverage * pow(1. + r, - dCoverage - 1);
            }
            return dDeriv;
        }
        
        ZSpreadNewton::ZSpreadNewton(const Bond & sBond, const Finance::Base::YieldCurve & sYieldCurve, double dPrice, std::size_t iNIterMax, double dTolerance, double dEpsValueDeriv) : Bond(sBond), NewtonRaphson1D(iNIterMax, dTolerance, dEpsValueDeriv), sYieldCurve_(sYieldCurve), dPrice_(dPrice)
        {}
        
        ZSpreadNewton::ZSpreadNewton(const Bond & sBond, const Finance::Base::YieldCurve & sYieldCurve, double dPrice) : Bond(sBond), NewtonRaphson1D(), sYieldCurve_(sYieldCurve), dPrice_(dPrice)
        {}
        
        double ZSpreadNewton::f(double r) const
        {
            double dRes = 0.;
            const Utilities::Date::MyDate & sToday = sYieldCurve_.Today();
            for (std::size_t iDate = 0 ; iDate < vCoupons_.size() ; ++iDate)
            {
                Utilities::Date::MyDate sEndDate = vCoupons_.at(iDate).GetEndDate();
                double dCoverage = Finance::Base::GetCoverage(sToday, sEndDate, vCoupons_.at(iDate).GetBasis());
                dRes += vCoupons_.at(iDate).GetCoupon() * pow(1. + sYieldCurve_(sEndDate.Diff(sToday)) + r, -dCoverage);
            }
            if (bIsNotionalRepaidBack_)
            {
                Utilities::Date::MyDate sEndDate = vCoupons_.back().GetEndDate();
                double dCoverage = Finance::Base::GetCoverage(sToday, sEndDate, vCoupons_.back().GetBasis());
                dRes += dNotional_ * pow(1. + sYieldCurve_(sEndDate.Diff(sToday)) + r, -dCoverage);
            }
            return dRes - dPrice_;
        }
        
        double ZSpreadNewton::df(double r) const
        {
            double dDeriv = 0.0;
            const Utilities::Date::MyDate&  sToday = sYieldCurve_.Today();
            for (std::size_t iDate = 0 ; iDate < vCoupons_.size() ; ++iDate)
            {
                double dCoverage = GetCoverage(sToday, vCoupons_.at(iDate).GetEndDate(), vCoupons_.at(iDate).GetBasis());
                dDeriv -= dCoverage * vCoupons_.at(iDate).GetCoupon() * pow(1. + r, - dCoverage - 1);
            }
            if (bIsNotionalRepaidBack_)
            {
                double dCoverage = GetCoverage(sToday, vCoupons_.back().GetEndDate(), vCoupons_.back().GetBasis());
                dDeriv -= dCoverage * pow(1. + r, - dCoverage - 1);
            }
            return dDeriv;
        }
        
        BondPricer::BondPricer(const Utilities::Date::MyDate & sStart, const Utilities::Date::MyDate & sEnd, const Finance::Base::YieldCurve & sYieldCurve, Finance::Base::MyBasis eBasis, Finance::Base::MyFrequency eFrequency, const std::vector<double> & dCoupons, double dNotional, bool bIsFixedRate, double dTolerance, std::size_t iNIterMax) : sYieldCurve_(sYieldCurve), dToleranceNewton_(dTolerance), iNIterMaxNewton_(iNIterMax), Bond(dNotional, true)
        {
            Create(dCoupons, sStart, sEnd, eBasis, eFrequency, bIsFixedRate, vCoupons_);
        }
        
        double BondPricer::Price() const
        {
            double dPrice = 0.;
            const Utilities::Date::MyDate & sToday = sYieldCurve_.Today();
            if (vCoupons_.size() > 0)
            {
                //  1st coupon
                if (vCoupons_.at(0).IsFixedRateCoupon())
                {
                    dPrice += vCoupons_.at(0).GetCoupon() * vCoupons_.at(0).GetPayingDateDF(sYieldCurve_);
                }
                else
                {
                    Finance::Instruments::DF sDF(sYieldCurve_);
                    dPrice += vCoupons_.at(0).GetCoupon() * (sDF(sToday) - vCoupons_.at(0).GetPayingDateDF(sYieldCurve_));
                }
                for (std::size_t iDate = 1 ; iDate < vCoupons_.size() ; ++iDate)
                {
                    if (vCoupons_[iDate].IsFixedRateCoupon())
                    {
                        dPrice += vCoupons_.at(iDate).GetCoupon() * vCoupons_.at(iDate).GetPayingDateDF(sYieldCurve_);
                    }
                    else
                    {
                        dPrice += vCoupons_.at(iDate).GetCoupon() * (vCoupons_.at(iDate - 1).GetPayingDateDF(sYieldCurve_) - vCoupons_.at(iDate).GetPayingDateDF(sYieldCurve_));
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
            const Utilities::Date::MyDate& sTodayDate = sYieldCurve_.Today();
            
            return vCoupons_.front().GetStartDate() < sTodayDate;
        }
        
        double BondPricer::CleanPrice() const
        {
            if (!HasAlreadyBegun())
            {
                return Price();
            }
            else
            {
                double dPrice = 0.;
                const Utilities::Date::MyDate& sTodayDate = sYieldCurve_.Today();
                
                if (vCoupons_.size() > 0)
                {
                    //  1st coupon
                    if (vCoupons_.at(0).GetStartDate() > sTodayDate)
                    {
                        if (vCoupons_.at(0).IsFixedRateCoupon())
                        {
                            dPrice += vCoupons_.at(0).GetCoupon() * vCoupons_.at(0).GetPayingDateDF(sYieldCurve_);
                        }
                        else
                        {
                            Finance::Instruments::DF sDF(sYieldCurve_);
                            dPrice += vCoupons_.at(0).GetCoupon() * (sDF(sTodayDate) - vCoupons_.at(0).GetPayingDateDF(sYieldCurve_));
                        }
                    }
                    for (std::size_t iDate = 1 ; iDate < vCoupons_.size() ; ++iDate)
                    {
                        if (vCoupons_[iDate].GetStartDate() > sTodayDate)
                        {
                            if (vCoupons_.at(iDate).IsFixedRateCoupon())
                            {
                                dPrice += vCoupons_.at(iDate).GetCoupon() * vCoupons_.at(iDate).GetPayingDateDF(sYieldCurve_);
                            }
                            else
                            {
                                dPrice += vCoupons_.at(iDate).GetCoupon() * (vCoupons_.at(iDate - 1).GetPayingDateDF(sYieldCurve_) - vCoupons_.at(iDate).GetPayingDateDF(sYieldCurve_));
                            }
                        }
                    }
                    if (bIsNotionalRepaidBack_)
                    {
                        dPrice += dNotional_ * vCoupons_.back().GetPayingDateDF(sYieldCurve_);
                    }
                }
                return dPrice;
            }
        }
        
        double BondPricer::DirtyPrice() const
        {
            if (!HasAlreadyBegun())
            {
                return Price();
            }
            else
            {
                return CleanPrice() + AccruedInterest();
            }
        }
        
        double BondPricer::PriceToYield(double dPrice) const
        {
            const Utilities::Date::MyDate & sToday = sYieldCurve_.Today();
            PriceToYieldNewton sNewtonClass(*this, sToday,dPrice);
            return sNewtonClass.algo_root_finder(0.0);
        }
        
        double BondPricer::I_Spread(double dPrice) const
        {
            const Utilities::Date::MyDate & sToday = sYieldCurve_.Today();
            const Utilities::Date::MyDate & endDate = vCoupons_.back().GetEndDate();
            const double diff = endDate.Diff(sToday);
            return PriceToYield(dPrice) - sYieldCurve_(diff);
        }
        
        double BondPricer::Z_Spread(double dPrice) const
        {
            ZSpreadNewton sZSpread(*this, sYieldCurve_, dPrice);
            return sZSpread.algo_root_finder(0.0);
        }
        
        double BondPricer::AccruedInterest() const
        {
            if (HasAlreadyBegun())
            {
                std::vector<Utilities::Date::MyDate> sStartDates;
                for (std::size_t iDate = 0 ; iDate < vCoupons_.size() ; ++iDate)
                {
                    sStartDates.push_back(vCoupons_[iDate].GetStartDate());
                }
                const Utilities::Date::MyDate& sTodayDate = sYieldCurve_.Today();
                
                int iFind = Utilities::FindInVector(sStartDates, sTodayDate);
                
                REQUIREEXCEPTION(iFind!=-1,"Today not found in start dates");
                return vCoupons_[iFind].GetPayingDateDF(sYieldCurve_) * Finance::Base::GetCoverage(sTodayDate, vCoupons_[iFind].GetEndDate(), vCoupons_[iFind].GetBasis()) * vCoupons_[iFind].GetCoupon();
            }
            else
            {
                return 0.0;
            }
        }
    }
}