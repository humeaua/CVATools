//
//  HermitePolynomials.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 10/02/14.
//
//

#include "HermitePolynomials.h"
#include "Exception.h"

namespace Maths
{
    HermitePolynomial::HermitePolynomial() : Polynomial(3)
    {}
    
    HermitePolynomial::~HermitePolynomial()
    {}
    
    double HermitePolynomial::deriv(double t, size_t i) const
    {
        switch (i)
        {
            case 0:
            {
                //return (2 * t * t * t - 3 * t * t + 1);
                return (6 * t * (t - 1));
            }
            case 1:
            {
                //return (t * t * t - 2 * t * t + t);
                return 3 * t * t - 4 * t;
            }
            case 2:
            {
                //return (-2. * t * t * t + 3. * t * t);
                return -6.0 * t * t + 6 * t;
            }
            case 3:
            {
                //return (t * t * t - t * t);
                return 3*t*t - 2*t;
            }
            default:
            {
                throw EXCEPTION("Index out of bounds : must be 0, 1, 2 or 3");
                break;
            }
        }
    }
    
    double HermitePolynomial::deriv2(double t, size_t i) const
    {
        switch (i)
        {
            case 0:
            {
                //return (2 * t * t * t - 3 * t * t + 1);
                //return (6 * t * (t - 1));
                return 12 * t - 6;
            }
            case 1:
            {
                //return (t * t * t - 2 * t * t + t);
                //return 3 * t * t - 4 * t;
                return 6 * t - 4;
            }
            case 2:
            {
                //return (-2. * t * t * t + 3. * t * t);
                //return -6.0 * t * t + 6 * t;
                return -12 * t + 6;
            }
            case 3:
            {
                //return (t * t * t - t * t);
                //return 3*t*t - 2*t;
                return 6 * t - 2;
            }
            default:
            {
                throw EXCEPTION("Index out of bounds : must be 0, 1, 2 or 3");
                break;
            }
        }
    }
    
    double HermitePolynomial::operator()(double t, size_t i) const
    {
        switch (i)
        {
            case 0:
            {
                return (2 * t * t * t - 3 * t * t + 1);
            }
            case 1:
            {
                return (t * t * t - 2 * t * t + t);
            }
            case 2:
            {
                return (-2. * t * t * t + 3. * t * t);
            }
            case 3:
            {
                return (t * t * t - t * t);
            }
            default:
            {
                throw EXCEPTION("Index out of bounds : must be 0, 1, 2 or 3");
                break;
            }
        }
    }
}