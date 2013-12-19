//
//  CorrelationTS.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 19/12/13.
//
//

#ifndef __CVATools__CorrelationTS__
#define __CVATools__CorrelationTS__

#include <iostream>
#include "TermStructure.h"

namespace Finance
{
    namespace Base
    {
        class CorrelationTS : public TermStructure<double,double>
        {
        public:
            CorrelationTS(const std::vector<double> & dTime,
                          const std::vector<double> & dCorrelations);
            
            virtual double operator() (double t) const;
        };
    }
}

#endif /* defined(__CVATools__CorrelationTS__) */
