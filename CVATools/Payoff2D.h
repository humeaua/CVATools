//
//  Payoff2D.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 07/04/13.
//
//

#ifndef CVATools_Payoff2D_h
#define CVATools_Payoff2D_h

class Payoff2D {
public:
    Payoff2D();
    virtual ~Payoff2D();
    
    virtual double pay(double s1, double s2) const = 0;
};

#endif
