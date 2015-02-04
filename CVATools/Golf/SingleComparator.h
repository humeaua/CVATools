//
//  SingleComparator.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 04/02/15.
//
//

#ifndef CVATools_SingleComparator_h
#define CVATools_SingleComparator_h

template <class C>
class SimpleComparator
{
    C m_stuffToCompare;
public:
    SimpleComparator(const C& c) : m_stuffToCompare(c)
    {}
    
    bool operator()(const C & c) const
    {
        return m_stuffToCompare == c;
    }
};

#endif
