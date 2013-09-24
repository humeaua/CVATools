//
//  HashTable.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 31/07/13.
//
//

#include "HashTable.h"

namespace Utiliites
{
    template<class C, class D>
    void HashTable<C,D>::print(std::ostream & out) const
    {
        for (std::tr1::unordered_map<std::string, std::string>::const_iterator it = this->begin() ; it != this->end() ; ++it)
        {
            out << it->first << " ; " << it->second << std::endl;
        }
    }
}