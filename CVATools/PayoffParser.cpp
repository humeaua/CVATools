//
//  PayoffParser.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 07/12/14.
//
//

#include "PayoffParser.h"
#include "StringUtilities.h"

namespace Finance
{
    namespace Payoff
    {
        PayoffParser::PayoffParser(const std::string & payoff) : m_value(0.0)
        {
            m_parser.DefineVar("S", &m_value);
            m_parser.SetExpr(payoff);
        }
        
        double PayoffParser::operator()(const double S) const
        {
            m_value = S;
            return m_parser.Eval();
        }
        
        BasePayoff1D* PayoffParser::clone() const
        {
            return new PayoffParser(*this);
        }
    }
}