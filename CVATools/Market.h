//
//  Market.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 08/12/13.
//
//

#ifndef __CVATools__Market__
#define __CVATools__Market__

#include <iostream>
#include "Date.h"

namespace Finance
{
    namespace Market
    {
        class Market
        {
        private:
            Utilities::Date::MyDate TodayDate_;
        protected:
            virtual void Load(const std::string & cMarketName) = 0;
        public:
            Market(const Utilities::Date::MyDate & TodayDate);
            
            //  Getter
            Utilities::Date::MyDate TodayDate() const;
        };
    }
}

#endif /* defined(__CVATools__Market__) */
