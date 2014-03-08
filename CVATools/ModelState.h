//
//  ModelState.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 08/12/13.
//
//

#ifndef __CVATools__ModelState__
#define __CVATools__ModelState__

#include <iostream>
#include <vector>

/*
 This class implements the base class of a model state : particular path of Monte-Carlo simulation is an example of such a model state 
 */

namespace Finance
{
    //  Forward declaration of Underlying class
    class Underlying;
    
    namespace Models
    {
        class ModelState
        {
        private:
            std::vector<Underlying*> Underlyings;
        };
    }
}

#endif /* defined(__CVATools__ModelState__) */
