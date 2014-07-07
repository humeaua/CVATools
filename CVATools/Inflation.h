//
//  Inflation.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 28/12/13.
//
//

#ifndef __CVATools__Inflation__
#define __CVATools__Inflation__

#include <iostream>
#include "Underlying.h"
#include "RateCurve.h"

namespace Finance
{
    namespace Underlyings
    {
        class Inflation : public Underlying
        {
        protected:
            virtual double operator()(const Utilities::Date::MyDate & date1) const;
            virtual double operator()(const Utilities::Date::MyDate & date1,
                                      const Utilities::Date::MyDate & date2) const;
            
        private:
            double dSpot;
            RateCurve NominalCurve, RealCurve;
        };
    }
}

#endif /* defined(__CVATools__Inflation__) */
