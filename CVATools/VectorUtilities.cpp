//
//  VectorUtilities.cpp
//  Seminaire
//
//  Created by Alexandre HUMEAU on 09/01/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "VectorUtilities.h"

namespace Utilities {
    bool AreEqual(const std::vector<double> & vect1, const std::vector<double> & vect2, double tolerance)
    {
        if (vect1.size() != vect2.size())
        {
            return false;
        }
        
        for (std::size_t i = 0 ; i < vect1.size() ; ++i)
        {
            if (fabs(vect1[i] - vect2[i]) > tolerance)
            {
                return false;
            }
        }
        
        return true;
    }
}