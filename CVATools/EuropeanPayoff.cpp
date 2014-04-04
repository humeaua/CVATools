//
//  EuropeanPayoff.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 28/02/14.
//
//

#include "EuropeanPayoff.h"
#include "Exception.h"

namespace Finance
{
    namespace Payoff
    {
        /*EuropeanPayoff::EuropeanPayoff(size_t iNDimensions) : m_iNDimensions(iNDimensions)
        {}
        
        double EuropeanPayoff::pay(const std::vector<double> & S) const
        {
            switch (m_iNDimensions) {
                case 1:
                    return pay1(S.at(0));
                case 2:
                    return pay2(S.at(0), S.at(1));
                default:
                    throw EXCEPTION("Dimension higher than 2 : not yet implemented");
           }
        }
        
        EuropeanPayoff::~EuropeanPayoff()
        {}*/
        
        double EuropeanPayoff1::pay(const DoubleVec &S) const
        {
            return pay1(S.at(0));
        }
        
        EuropeanPayoff1::~EuropeanPayoff1()
        {}
        
        double EuropeanPayoff2::pay(const DoubleVec &S) const
        {
            return pay2(S.at(0), S.at(0));
        }
        
        EuropeanPayoff2::~EuropeanPayoff2()
        {}
    }
}