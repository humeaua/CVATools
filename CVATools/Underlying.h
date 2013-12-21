//
//  Underlying.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 08/12/13.
//
//

#ifndef __CVATools__Underlying__
#define __CVATools__Underlying__

#include <iostream>
#include "Date.h"
#include "Market.h"
#include "ModelState.h"

/*
 This class implements the base class of an underlying 
 */

namespace Finance
{
    //  Forward Declaration of ModelState class
    class ModelState;
    
    namespace Underlyings
    {
        class Underlying
        {
        protected:
            //  Need for now two declaration of the methods depending on the signatures of the methods as I do not know yet how to handle the arguments
            virtual double Spot(const Utilities::Date::MyDate & SpotDate, const Finance::Market::Market & Market) const = 0;
            
            virtual double Forward(const Utilities::Date::MyDate & FixingDate,
                                   const Utilities::Date::MyDate & SettleDate,
                                   const Finance::Market::Market & Market) const = 0;
            
            virtual double Spot(const Utilities::Date::MyDate & SpotDate,
                                const Finance::Market::Market & Market,
                                const ModelState & ModelState) const = 0;
            
            virtual double Forward(const Utilities::Date::MyDate & FixingDate,
                                   const Utilities::Date::MyDate & SettleDate,
                                   const Finance::Market::Market & Market,
                                   const ModelState & ModelState) const = 0;
        };
    }
}

#endif /* defined(__CVATools__Underlying__) */
