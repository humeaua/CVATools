//
//  PairComparatorFirst.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 17/12/14.
//
//

#ifndef __CVATools__StringComparator__
#define __CVATools__StringComparator__

#include <iostream>

template<class ID, class Object>
class PairComparatorFirst
{
private:
    ID m_str;
public:
    PairComparatorFirst(const ID & name) : m_str(name)
    {}
    
    bool operator()(const std::pair<ID, Object> & rhs) const
    {
        return rhs.first == m_str;
    }
    
    bool operator<(const std::pair<ID, Object> & rhs) const
    {
        return rhs.first > m_str;
    }
};

#endif /* defined(__CVATools__StringComparator__) */
