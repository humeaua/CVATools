//
//  LGMSVUnderlying.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 11/07/14.
//
//

#ifndef __CVATools__LGMSVUnderlying__
#define __CVATools__LGMSVUnderlying__

#include <iostream>
#include "RateUnderlying.h"
#include "TermStructure.h"

namespace SLV
{
    class LGM1FSVUnderlying : public RateUnderlying
    {
    public:
        LGM1FSVUnderlying(const Finance::Base::YieldCurve & yieldCurve);
        
        RateUnderlying * clone() const;
    private:
        // Term structure of volatility
        Finance::Base::TermStructure<double, double> m_Sigma;
        // Mean reversion - no term structure
        double m_Lambda;
        
        //  Correlation between rate and stoch vol
        double m_Rho;
        
        //  Stoch vol
        double m_StochVol;
    };
}

#endif /* defined(__CVATools__LGMSVUnderlying__) */
