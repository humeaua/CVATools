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
        //  Need default constructor for correlation market
        CorrelationTS::CorrelationTS()
        {}
        
        CorrelationTS::CorrelationTS(const std::vector<double> & dTime,
                                     const std::vector<double> & dCorrelations) : TermStructure<double, double>(dTime, dCorrelations)
        {}
    }
}