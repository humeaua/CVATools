//
//  PayoffMargrabe.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 07/04/13.
//
//

#ifndef CVATools_PayoffMargrabe_h
#define CVATools_PayoffMargrabe_h

#include "BasePayoff.h"

namespace Finance
{
    namespace Payoff
    {
        class PayoffMargrabe : public BasePayoff2D
        {
        protected:
            double dK_;
            
        public:
            PayoffMargrabe(double dK);
            
            virtual double operator()(const double s1, const double s2) const;
            virtual BasePayoff2D * clone() const;
        };
    }
}

#endif
