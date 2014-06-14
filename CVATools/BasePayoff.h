//
//  BasePayoff1D.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 28/02/14.
//
//

#ifndef __CVATools__EuropeanPayoff__
#define __CVATools__EuropeanPayoff__

#include <iostream>
#include <vector>
#include "Require.h"

namespace Finance
{
    namespace Payoff
    {
        class BasePayoff1D
        {
        public:
            virtual double operator()(const double S) const = 0;
            virtual ~BasePayoff1D();
            
            virtual BasePayoff1D * clone() const = 0;
        };

        class BasePayoff2D
        {
        public:
            virtual double operator()(const double S1, const double S2) const = 0;
            virtual ~BasePayoff2D();
            
            virtual BasePayoff2D * clone() const = 0;
        };
    }
}

#endif /* defined(__CVATools__GenericPayoff__) */
