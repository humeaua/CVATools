//
//  ObservableLibor.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 05/07/13.
//
//

#ifndef __CVATools__ObservableLibor__
#define __CVATools__ObservableLibor__

#include <iostream>
#include "Observable.h"
#include "YieldCurve.h"

namespace Finance
{
    namespace Observables
    {
        class ObservableLibor : public Observable
        {
        protected:
            int iLag_;
            int iTenor_;
            Finance::Base::YieldCurve sYC_;
            std::string cCurrency_;
        public:
            ObservableLibor(const std::string & cCCY,
                            const Finance::Base::YieldCurve & sYC,
                            int iLag,
                            int iTenor);
            
            virtual double Observe(const long & lDate) const = 0;
            virtual std::vector<double> Observe(const std::vector<long>& lDates) const = 0;
        };
    }
}

#endif /* defined(__CVATools__ObservableLibor__) */
