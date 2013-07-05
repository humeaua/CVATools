//
//  ObservableLibor.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 05/07/13.
//
//

#include "ObservableLibor.h"

namespace Finance
{
    namespace Observables
    {
        ObservableLibor::ObservableLibor(const std::string & cCCY,
                                         const Finance::Base::YieldCurve & sYC,
                                         int iLag) : Observable("LIBOR",cCCY,""), sYC_(sYC), iLag_(iLag)
        {}
    }
}