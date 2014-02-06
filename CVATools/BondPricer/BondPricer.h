//
//  BondPricer.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 11/05/13.
//
//

#ifndef CVATools_BondPricer_h
#define CVATools_BondPricer_h

#include "Schedule.h"
#include "Bond.h"
#include "NewtonRaphson.h"

namespace Finance
{
    namespace Pricers
    {
        class PriceToYieldNewton : public Maths::NewtonRaphson1D, public Instruments::Bond
        {
        protected:
            double dPrice_;
            Utilities::Date::MyDate sToday_;
        public:
            PriceToYieldNewton(const Bond & sBond,
                               const Utilities::Date::MyDate & sToday,
                               double dPrice,
                               std::size_t iNIterMax,
                               double dTolerance,
                               double dEpsValueDeriv);
            PriceToYieldNewton(const Bond & sBond,
                               const Utilities::Date::MyDate & sToday,
                               double dPrice);
            virtual double f(double x) const;
            virtual double df(double x) const;
        };
        
        class ZSpreadNewton : public Maths::NewtonRaphson1D, public Instruments::Bond
        {
        protected:
            Finance::Base::YieldCurve sYieldCurve_;
            double dPrice_;
        public:
            ZSpreadNewton(const Bond & sBond,
                          const Finance::Base::YieldCurve & sYieldCurve,
                          double dPrice,
                          std::size_t iNIterMax,
                          double dTolerance,
                          double dEpsValueDeriv);
            ZSpreadNewton(const Bond & sBond,
                          const Finance::Base::YieldCurve & sYieldCurve,
                          double dPrice);
            virtual double f(double x) const;
            virtual double df(double x) const;
        };
        
        class BondPricer : public Instruments::Bond
        {
        protected:
            Finance::Base::YieldCurve sYieldCurve_;
            
            //  Newton parameters
            double dToleranceNewton_;
            std::size_t iNIterMaxNewton_;
            
            virtual double AccruedInterest() const;
            
        public:
            BondPricer(const Utilities::Date::MyDate & sStart, const Utilities::Date::MyDate & sEnd, const Finance::Base::YieldCurve & sYieldCurve, Finance::Base::MyBasis eBasis, Finance::Base::MyFrequency eFrequency, const std::vector<double>  & dCoupons, double dNotional, bool bIsFixedRate, double dToleranceNewton = 1e-06, std::size_t iNIterMaxNewton = 100);
            
            virtual double Price() const;
            
            virtual bool HasAlreadyBegun() const;
            virtual double CleanPrice() const;
            virtual double DirtyPrice() const;
            
            //  Only for fixed coupon Bond
            virtual double PriceToYield(double dPrice) const;
            virtual double I_Spread(double dPrice) const;
            virtual double Z_Spread(double dPrice) const;
        };
    }
}

#endif
