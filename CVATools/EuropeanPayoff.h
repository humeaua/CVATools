//
//  EuropeanPayoff.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 28/02/14.
//
//

#ifndef __CVATools__EuropeanPayoff__
#define __CVATools__EuropeanPayoff__

#include <iostream>
#include <vector>

namespace Finance
{
    namespace Payoff
    {
        //  Base class for all payoffs
        class EuropeanPayoff
        {
        protected:
            size_t m_iNDimensions;
            
            virtual double pay1(double s1) const = 0;
            virtual double pay2(double s1, double s2) const = 0;
        public:
            EuropeanPayoff(size_t iNDimensions);
            virtual ~EuropeanPayoff();
            virtual double pay(const std::vector<double> & S) const;
        };
    }
}

#endif /* defined(__CVATools__GenericPayoff__) */
