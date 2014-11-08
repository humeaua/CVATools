//
//  HashTable.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 31/07/13.
//
//

#ifndef __CVATools__HashTable__
#define __CVATools__HashTable__

#include <iostream>
#include <tr1/unordered_map>

namespace Utilities {
    
    template<class C, class D> class HashTable : public std::tr1::unordered_map<C, D>
    {
        typedef typename std::tr1::unordered_map<C, D>::const_iterator const_iterator;
    public:
        virtual void print(std::ostream & os = std::cout) const
        {
            for (const_iterator it = this->begin() ; it != this->end() ; ++it)
            {
                os << it->first << " ; " << it->second << std::endl;
            }
        }
    };
}

#endif /* defined(__CVATools__HashTable__) */
