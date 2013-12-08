//
//  Model.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 08/12/13.
//
//

#ifndef __CVATools__Model__
#define __CVATools__Model__

#include <iostream>
#include <vector>
#include "ModelState.h"

/*
 This class is the base class of models : need to implement fx, rates, equity models as derived class of this base class
 */

namespace Finance
{
    namespace Models
    {
        class Model
        {
        private:
            std::vector<ModelState> sStates_;
        };
    }
}

#endif /* defined(__CVATools__Model__) */
