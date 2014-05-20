//
//  Expression.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 20/05/14.
//
//

#ifndef CVATools_Expression_h
#define CVATools_Expression_h

#include <stack>

namespace AD
{
    // implementation from http://www.met.reading.ac.uk/clouds/publications/adept.pdf
    
    template<class A>
    struct Expression
    {
        const A& cast() const
        {
            return static_cast<const A&>(*this);
        }
        
        double value() const
        {
            return cast().value();
        }
        
        void calc_gradient(const std::stack<A>& stack) const
        {
            cast().calc_gradient(stack);
        }
        
        void calc_gradient(const std::stack<A> & stack, double multiplier) const
        {
            cast().calc_gradient(stack, multiplier);
        }
    }
}

#endif
