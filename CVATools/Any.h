//
//  Any.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 08/03/14.
//
//

#ifndef CVATools_Any_h
#define CVATools_Any_h

// See http://www.boost.org/libs/any for Documentation.

// what:  variant type boost::any
// who:   contributed by Kevlin Henney,
//        with features contributed and bugs found by
//        Ed Brey, Mark Rodgers, Peter Dimov, and James Curran
// when:  July 2001
// where: tested with BCC 5.5, MSVC 6.0, and g++ 2.95

#include <algorithm>
#include <typeinfo>
#include "Exception.h"

// See boost/python/type_id.hpp
# if (defined(__GNUC__) && __GNUC__ >= 3) \
|| defined(_AIX) \
|| (   defined(__sgi) && defined(__host_mips)) \
|| (defined(__hpux) && defined(__HP_aCC)) \
|| (defined(linux) && defined(__INTEL_COMPILER) && defined(__ICC))
#  define BOOST_AUX_ANY_TYPE_ID_NAME
#include <cstring>
# endif

namespace boost
{
    class any
    {
    public: // structors
        
        any()
        : content(0)
        {
        }
        
        template<typename ValueType>
        any(const ValueType & value)
        : content(new holder<ValueType>(value))
        {
        }
        
        any(const any & other)
        : content(other.content ? other.content->clone() : 0)
        {
        }
        
        ~any()
        {
            delete content;
        }
        
    public: // modifiers
        
        any & swap(any & rhs)
        {
            std::swap(content, rhs.content);
            return *this;
        }
        
        template<typename ValueType>
        any & operator=(const ValueType & rhs)
        {
            any(rhs).swap(*this);
            return *this;
        }
        
        any & operator=(any rhs)
        {
            rhs.swap(*this);
            return *this;
        }
        
    public: // queries
        
        bool empty() const
        {
            return !content;
        }
        
        const std::type_info & type() const
        {
            return content ? content->type() : typeid(void);
        }
        
    public: // types (public so any_cast can be non-friend)
        
        class placeholder
        {
        public: // structors
            
            virtual ~placeholder()
            {
            }
            
        public: // queries
            
            virtual const std::type_info & type() const = 0;
            
            virtual placeholder * clone() const = 0;
            
        };
        
        template<typename ValueType>
        class holder : public placeholder
        {
        public: // structors
            
            holder(const ValueType & value)
            : held(value)
            {
            }
            
        public: // queries
            
            virtual const std::type_info & type() const
            {
                return typeid(ValueType);
            }
            
            virtual placeholder * clone() const
            {
                return new holder(held);
            }
            
        public: // representation
            
            ValueType held;
            
        private: // intentionally left unimplemented
            holder & operator=(const holder &);
        };        
    public: // representation (public so any_cast can be non-friend)
        placeholder * content;
        
    };
    
    class bad_any_cast : public std::bad_cast
    {
    public:
        virtual const char * what() const throw()
        {
            return "boost::bad_any_cast: failed conversion using boost::any_cast";
        }
    };
    
    template<typename ValueType>
    ValueType * any_cast(any * operand)
    {
        if (operand && std::strcmp(operand->type().name(), typeid(ValueType).name()) == 0)
        {
            return static_cast<any::holder<ValueType> *>(operand->content)->held;
        }
        else
        {
            return 0;
        }
    }
    
    template<typename ValueType>
    inline const ValueType * any_cast(const any * operand)
    {
        return any_cast<ValueType>(const_cast<any *>(operand));
    }
    
    template<typename ValueType>
    ValueType any_cast(any & operand)
    {
        typedef typename std::tr1::remove_reference<ValueType>::type nonref;        
        nonref * result = any_cast<nonref>(&operand);
        if(!result)
            throw EXCEPTION(bad_any_cast().what());
        return *result;
    }
    
    template<typename ValueType>
    inline ValueType any_cast(const any & operand)
    {
        typedef typename std::tr1::remove_reference<ValueType>::type nonref;
        return any_cast<const nonref &>(const_cast<any &>(operand));
    }
    
    // Note: The "unsafe" versions of any_cast are not part of the
    // public interface and may be removed at any time. They are
    // required where we know what type is stored in the any and can't
    // use typeid() comparison, e.g., when our types may travel across
    // different shared libraries.
    template<typename ValueType>
    inline ValueType * unsafe_any_cast(any * operand)
    {
        return &static_cast<any::holder<ValueType> *>(operand->content)->held;
    }
    
    template<typename ValueType>
    inline const ValueType * unsafe_any_cast(const any * operand)
    {
        return unsafe_any_cast<ValueType>(const_cast<any *>(operand));
    }
}

// Copyright Kevlin Henney, 2000, 2001, 2002. All rights reserved.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#endif
