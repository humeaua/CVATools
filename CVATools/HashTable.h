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

namespace Utiliites {
    
    template<class C, class D> class HashTable : public std::tr1::unordered_map<C, D>
    {
    public:
        virtual void print(std::ostream & out = std::cout) const;
    };
}


#endif /* defined(__CVATools__HashTable__) */
