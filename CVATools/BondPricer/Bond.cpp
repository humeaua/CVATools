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
#include "DateShifter.h"

namespace Finance
{
    namespace Instruments
    {
        void CreateBond(//  Inputs
                        const std::vector<double> & dCoupons,
                        const Utilities::Date::MyDate & sStart,
                        const Utilities::Date::MyDate & sEnd,
                        Finance::Base::MyBasis eBasis,
                        Finance::Base::MyFrequency eFrequency,
                        bool bIsFixedRate,
                        //  Output
                        std::vector<Base::Coupon> & vCoupons)
        {
            Finance::Base::Schedule sSchedule(sStart, sEnd, eBasis, eFrequency, Finance::Base::DateShifter(0, Utilities::Date::DAY),Finance::Base::DateShifter(0, Utilities::Date::DAY));
            
            std::vector<Finance::Base::EventOfSchedule> vSchedule = sSchedule.GetSchedule();
            REQUIREEXCEPTION(vSchedule.size() == dCoupons.size(), "CreateBond : Coupon and Schedule do not have the same size. Cannot create Bond");
            
            for (std::size_t iDate = 0 ; iDate < vSchedule.size() ; ++iDate)
            {
                vCoupons.push_back(Base::Coupon(dCoupons[iDate], bIsFixedRate, vSchedule[iDate].GetStartDate(), vSchedule[iDate].GetEndDate(), vSchedule[iDate].GetBasis()));
            }
        }
        
        void CreateBond(//  Inputs
                        const std::vector<double> & dCoupons,
                        const Utilities::Date::MyDate & sStart,
                        const Utilities::Date::MyDate & sEnd,
                        Finance::Base::MyBasis eBasis,
                        Finance::Base::MyFrequency eFrequency,
                        const std::vector<bool> & bIsFixedRate,
                        //  Output
                        std::vector<Base::Coupon> & vCoupons)
        {
            Finance::Base::Schedule sSchedule(sStart, sEnd, eBasis, eFrequency, Finance::Base::DateShifter(0, Utilities::Date::DAY),Finance::Base::DateShifter(0, Utilities::Date::DAY));
            
            std::vector<Finance::Base::EventOfSchedule> vSchedule = sSchedule.GetSchedule();
            REQUIREEXCEPTION(vSchedule.size() == dCoupons.size(), "Coupon and Schedule do not have the same size. Cannot create Bond");
            REQUIREEXCEPTION(vSchedule.size() != bIsFixedRate.size(), "Coupon and Fixed Rate boolean do not the same size. Cannot create Bond");
            
            for (std::size_t iDate = 0 ; iDate < vSchedule.size() ; ++iDate)
            {
                vCoupons.push_back(Finance::Base::Coupon(dCoupons[iDate], bIsFixedRate[iDate], vSchedule[iDate].GetStartDate(), vSchedule[iDate].GetEndDate(), vSchedule[iDate].GetBasis()));
            }
        }
        
        Bond::Bond(double dNotional, bool bIsNotionalRepaidBack) : dNotional_(dNotional), bIsNotionalRepaidBack_(bIsNotionalRepaidBack)
        {}
        
        Bond::Bond(double dNotional, bool bIsNotionalRepaidBack, const std::vector<Base::Coupon> & vCoupons) : bIsNotionalRepaidBack_(bIsNotionalRepaidBack), vCoupons_(vCoupons)
        {}
    }
}