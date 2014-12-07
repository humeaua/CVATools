//
//  PayoffParser.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 07/12/14.
//
//

#ifndef __CVATools__PayoffParser__
#define __CVATools__PayoffParser__

#include <iostream>
#include "BasePayoff.h"
#include "muParser.h"

namespace Finance
{
    namespace Payoff
    {
        class PayoffParser : public BasePayoff1D
        {
        protected:
            mu::Parser m_parser;
            mutable mu::value_type m_value;
        public:
            PayoffParser(const std::string & payoff);
            virtual double operator()(const double S) const;
            
            virtual BasePayoff1D * clone() const;
        };
    }
}

#endif /* defined(__CVATools__PayoffParser__) */
