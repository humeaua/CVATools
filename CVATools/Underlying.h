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
        public:
            //  Need for now two declaration of the methods depending on the signatures of the methods as I do not know yet how to handle the arguments
            virtual double operator()(const Utilities::Date::MyDate & date1) const = 0;
            virtual double operator()(const Utilities::Date::MyDate & date1,
                                      const Utilities::Date::MyDate & date2) const;
        };
    }
}

#endif /* defined(__CVATools__Underlying__) */
