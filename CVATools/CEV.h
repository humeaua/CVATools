//
//  CEV.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 23/02/14.
//
//

#ifndef __CVATools__CEV__
#define __CVATools__CEV__

#include <iostream>
#include "LocalVolatility.h"

namespace Finance
{
    namespace Processes
    {
        class CEV : public Finance::Processes::LocalVolatility
        {
        protected:
            double m_beta;
        public:
            CEV(double beta, double x0, long long & lSeed);
            
            virtual double SigmaLoc(double t, double dS) const;
            virtual double drift(double t, double S) const;
        };
    }
}

#endif /* defined(__CVATools__CEV__) */
