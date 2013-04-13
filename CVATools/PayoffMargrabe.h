//
//  PayoffMargrabe.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 07/04/13.
//
//

#ifndef CVATools_PayoffMargrabe_h
#define CVATools_PayoffMargrabe_h

#include "Payoff2D.h"

class PayoffMargrabe : public Payoff2D
{
protected:
    double dK_;
    
public:
    PayoffMargrabe(double dK);
    ~PayoffMargrabe();
    
    virtual double pay(double s1, double s2) const;
};

#endif
