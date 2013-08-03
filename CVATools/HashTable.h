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
    
    class HashTable : public std::tr1::unordered_map<std::string, std::string>
    {
    protected:
    public:
        virtual void print() const;
    };
}


#endif /* defined(__CVATools__HashTable__) */
