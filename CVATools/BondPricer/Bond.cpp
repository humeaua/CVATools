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

namespace
{
        void CreateBond(//  Inputs
                        const std::vector<double> & dCoupons,
                        const Utilities::Date::MyDate & sStart,
                        const Utilities::Date::MyDate & sEnd,
                        Finance::Base::MyBasis eBasis,
                        Finance::Base::MyFrequency eFrequency,
                        bool bIsFixedRate,
                        const Utilities::HolidaysPtr & holidays,
                        //  Output
                        std::vector<std::tr1::shared_ptr<Finance::Base::Coupon> > & vCoupons)
        {
            Finance::Base::Schedule sSchedule(sStart,
                                              sEnd,
                                              eBasis,
                                              eFrequency,
                                              Finance::Base::DateShifter_Ptr(new Finance::Base::DateShifterSimple(2, Utilities::Date::BUSINESSDAY, holidays)),
                                              holidays);
            
            std::vector<std::tr1::shared_ptr<Finance::Base::EventOfSchedule> > vSchedule = sSchedule.GetSchedule();
            REQUIREEXCEPTION(vSchedule.size() == dCoupons.size(), "CreateBond : Coupon and Schedule do not have the same size. Cannot create Bond");
            
            for (std::size_t iDate = 0 ; iDate < vSchedule.size() ; ++iDate)
            {
                vCoupons.push_back(std::tr1::shared_ptr<Finance::Base::Coupon>(new Finance::Base::Coupon(dCoupons[iDate], bIsFixedRate, vSchedule[iDate]->GetStartDate(), vSchedule[iDate]->GetEndDate(), vSchedule[iDate]->GetBasis(), holidays)));
            }
        }
}
namespace Finance
{
    namespace Instruments
    {
        
        Bond::Bond(double dNotional, bool bIsNotionalRepaidBack) : dNotional_(dNotional), bIsNotionalRepaidBack_(bIsNotionalRepaidBack)
        {}
        
        Bond::Bond(double dNotional, bool bIsNotionalRepaidBack, const std::vector<std::tr1::shared_ptr<Base::Coupon> > & vCoupons) : bIsNotionalRepaidBack_(bIsNotionalRepaidBack), vCoupons_(vCoupons)
        {}
        
        void Bond::Create(const std::vector<double> &dCoupons, const Utilities::Date::MyDate &sStart, const Utilities::Date::MyDate &sEnd, Finance::Base::MyBasis eBasis, Finance::Base::MyFrequency eFrequency, bool bIsFixedRate, const Utilities::HolidaysPtr& holidays, std::vector<std::tr1::shared_ptr<Base::Coupon> > &vCoupons)
        {
            m_holidays = holidays; // set the holidays for S-Spread and Z-spread
            CreateBond(//  Inputs
                       dCoupons,
                       sStart,
                       sEnd,
                       eBasis,
                       eFrequency,
                       bIsFixedRate,
                       holidays,
                       //  Output
                       vCoupons);
        }
    }
}