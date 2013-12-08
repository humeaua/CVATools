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

namespace Finance
{
    namespace Market
    {
        class Market
        {
        public:
            Market(const std::string & cMarketName);
            
        protected:
            virtual void Load(const std::string & cMarketName) = 0;
        };
    }
}

#endif /* defined(__CVATools__Market__) */
