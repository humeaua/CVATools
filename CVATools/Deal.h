//
//  Deal.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 21/01/14.
//
//

#ifndef __CVATools__Deal__
#define __CVATools__Deal__

#include <iostream>
#include <vector>
#include "Leg.h"
#include <tr1/memory>

namespace Finance
{
    namespace Deal
    {
        class Deal
        {
        protected:
            std::vector<std::tr1::shared_ptr<Leg> > Legs_;
            
        public:
            Deal(const std::vector<std::tr1::shared_ptr<Leg> > & Legs);
            
            virtual double Price(const std::vector<Finance::Models::Model> & models, const std::string &reportingCurrency) const;
        };
    }
}

#endif /* defined(__CVATools__Deal__) */
