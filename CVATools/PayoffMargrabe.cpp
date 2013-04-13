//
//  PayoffMargrabe.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 13/04/13.
//
//

#include "PayoffMargrabe.h"
#include <iostream>

PayoffMargrabe::PayoffMargrabe(double dK) : dK_(dK)
{}

PayoffMargrabe::~PayoffMargrabe()
{}

double PayoffMargrabe::pay(double s1, double s2) const
{
    return std::max(s1 - dK_ * s2, 0.0);
}