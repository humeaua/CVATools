//
//  PayoffVanillaOption.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 07/04/13.
//
//

#ifndef CVATools_PayoffVanillaOption_h
#define CVATools_PayoffVanillaOption_h

#include "Payoff.h"

typedef enum
{
    CALL,
    PUT,
    STRADDLE
}VanillaOptionType;

class PayoffVanillaOption {
protected:
    double dStrike_;
    VanillaOptionType eOptionType_;
public:
    PayoffVanillaOption(double dStrike, VanillaOptionType eOptionType_);
    virtual ~PayoffVanillaOption();
    
    virtual double pay(double dS) const;
};

#endif
