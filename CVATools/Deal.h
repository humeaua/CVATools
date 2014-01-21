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

namespace Finance
{
    namespace Deal
    {
        class Deal
        {
        protected:
            std::vector<Leg*> Legs_;
            
        public:
            Deal(const std::vector<Leg*> & Legs);
            
            virtual double Price(const std::vector<Finance::Models::Model> & models) const;
        };
    }
}

#endif /* defined(__CVATools__Deal__) */
