//
//  Deal.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 21/01/14.
//
//

#include "Deal.h"
#include "Require.h"

namespace Finance
{
    namespace Deal
    {
        Deal::Deal(const std::vector<Leg*> & Legs) : Legs_(Legs)
        {}
        
        double Deal::Price(const std::vector<Models::Model> & models, const std::string& reportingCurrency) const
        {
            REQUIREEXCEPTION(models.size() == Legs_.size(), "Models and Legs are not the same size : cannot price deal");
            double price = 0.0;
            std::vector<Finance::Models::Model>::const_iterator model = models.begin();
            for (std::vector<Leg*>::const_iterator leg = Legs_.begin() ; leg != Legs_.end() ; ++leg, ++model)
            {
                price += (*leg)->Price(*model, reportingCurrency);
            }
            
            return price;
        }
    }
}