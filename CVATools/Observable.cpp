//
//  Observable.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 05/07/13.
//
//

#include "Observable.h"

namespace Finance
{
    namespace Observables
    {
        Observable::Observable(const std::string & cType, const std::string & cDomCCY, const std::string & cForCCY) : cType_(cType), cForCCY_(cForCCY), cDomCCY_(cDomCCY)
        {}
    }
}