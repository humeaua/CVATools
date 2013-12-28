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
        PriceToYieldNewton::PriceToYieldNewton(const Bond & sBond, const Utilities::Date::MyDate & sToday, double dPrice, std::size_t iNIterMax, double dTolerance, double dEpsValueDeriv) : Bond(sBond), NewtonRaphson1D(iNIterMax, dTolerance, dEpsValueDeriv), sToday_(sToday),dPrice_(dPrice)
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
        
        ZSpreadNewton::ZSpreadNewton(const Bond & sBond, const Finance::Base::YieldCurve & sYieldCurve, const Utilities::Date::MyDate & sToday, double dPrice, std::size_t iNIterMax, double dTolerance, double dEpsValueDeriv) : Bond(sBond), NewtonRaphson1D(iNIterMax, dTolerance, dEpsValueDeriv), sYieldCurve_(sYieldCurve), dPrice_(dPrice), sToday_(sToday)
        {}
        
        double ZSpreadNewton::f(double r) const
        {
            double dRes = 0.;
            for (std::size_t iDate = 0 ; iDate < vCoupons_.size() ; ++iDate)
            {
                Utilities::Date::MyDate sEndDate = vCoupons_.at(iDate).GetEndDate();
                double dCoverage = Finance::Base::GetCoverage(sToday_, sEndDate, vCoupons_.at(iDate).GetBasis());
                dRes += vCoupons_.at(iDate).GetCoupon() * pow(1. + sYieldCurve_(sEndDate.Diff(sToday_)) + r, -dCoverage);
            }
            if (bIsNotionalRepaidBack_)
            {
                Utilities::Date::MyDate sEndDate = vCoupons_.back().GetEndDate();
                double dCoverage = Finance::Base::GetCoverage(sToday_, sEndDate, vCoupons_.back().GetBasis());
                dRes += dNotional_ * pow(1. + sYieldCurve_(sEndDate.Diff(sToday_)) + r, -dCoverage);
            }
            return dRes - dPrice_;
        }
        
        double ZSpreadNewton::df(double r) const
        {
            double dDeriv = 0.0;
            Utilities::Date::MyDate sToday = Utilities::Date::InitializeTodayDate();
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
        
        BondPricer::BondPricer(const Utilities::Date::MyDate & sToday, const Utilities::Date::MyDate & sStart, const Utilities::Date::MyDate & sEnd, const Finance::Base::YieldCurve & sYieldCurve, Finance::Base::MyBasis eBasis, Finance::Base::MyFrequency eFrequency, const DVector & dCoupons, double dNotional, bool bIsFixedRate, double dTolerance, std::size_t iNIterMax) : sYieldCurve_(sYieldCurve), dToleranceNewton_(dTolerance), iNIterMaxNewton_(iNIterMax), Bond(dNotional, true), sToday_(sToday)
        {
            Instruments::CreateBond(dCoupons, sStart, sEnd, eBasis, eFrequency, bIsFixedRate, vCoupons_);
        }
        
        double BondPricer::Price() const
        {
            double dPrice = 0.;
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
                    dPrice += vCoupons_.at(0).GetCoupon() * (sDF(sToday_) - vCoupons_.at(0).GetPayingDateDF(sYieldCurve_));
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
            Utilities::Date::MyDate sTodayDate = Utilities::Date::InitializeTodayDate();
            
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
                Utilities::Date::MyDate sTodayDate = Utilities::Date::InitializeTodayDate();
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
            PriceToYieldNewton sNewtonClass(*this, sToday_,dPrice);
            return sNewtonClass.algo_root_finder(0.0);
        }
        
        double BondPricer::I_Spread(double dPrice) const
        {
            return PriceToYield(dPrice) - sYieldCurve_(vCoupons_.back().GetEndDate().Diff(sToday_));
        }
        
        double BondPricer::Z_Spread(double dPrice) const
        {
            ZSpreadNewton sZSpread(*this, sYieldCurve_, sToday_,dPrice);
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
                Utilities::Date::MyDate sTodayDate = Utilities::Date::InitializeTodayDate();
                
                int iFind = Utilities::FindInVector(sStartDates, sTodayDate);
                return vCoupons_[iFind].GetPayingDateDF(sYieldCurve_) * Finance::Base::GetCoverage(sTodayDate, vCoupons_[iFind].GetEndDate(), vCoupons_[iFind].GetBasis()) * vCoupons_[iFind].GetCoupon();
            }
            else
            {
                return 0.0;
            }
        }
    }
}