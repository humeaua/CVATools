//
//  CorrelationTS.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 19/12/13.
//
//

#include "CorrelationTS.h"

namespace Finance
{
    namespace Base
    {
        CorrelationTS::CorrelationTS(const std::vector<double> & dTime,
                                     const std::vector<double> & dCorrelations) : TermStructure<double, double>(dTime, dCorrelations)
        {}
        
        double CorrelationTS::operator()(double t) const
        {
            return Interpolate(t);
        }
    }
}