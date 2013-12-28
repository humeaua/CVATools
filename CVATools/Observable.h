//
//  Observable.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 05/07/13.
//
//

#ifndef __CVATools__Observable__
#define __CVATools__Observable__

#include <iostream>
#include <vector>

/*
 This class defines a base observable class : libor, fx spot, swap rates ... are observables
 */

namespace Finance
{
    namespace Observables
    {
        class Observable
        {
        protected:
            std::string cType_;
        public:
            Observable(const std::string & cType);
    
            virtual double Observe(const long & lDate) const = 0;
            virtual std::vector<double> Observe(const std::vector<long>& lDates) const = 0;
        };
    }
}

#endif /* defined(__CVATools__Observable__) */
