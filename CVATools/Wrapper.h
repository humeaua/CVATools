//
//  Wrapper.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 04/05/14.
//
//

#ifndef CVATools_Wrapper_h
#define CVATools_Wrapper_h

namespace Utilities
{
    template<typename T>
    class Wrapper
    {
    public:
        Wrapper() : ptr(0)
        {}
        
        Wrapper(const T & rhs) : ptr (rhs.clone())
        {}
        
        ~Wrapper()
        {
            delete ptr;
        }
        
        Wrapper(const Wrapper<T> & rhs)
        {
            if (rhs.ptr)
            {
                ptr = rhs.ptr.clone();
            }
            else
            {
                ptr = 0;
            }
        }
        
        Wrapper & operator= (const Wrapper<T> & original)
        {
            if (this != original)
            {
                if (ptr != 0)
                {
                    delete ptr;
                }
                
                if (original.ptr)
                {
                    ptr = original.ptr.clone();
                }
                else
                {
                    ptr = 0;
                }
            }
            return *this;
        }
        
        T& operator*()
        {
            return *ptr;
        }
        
        const T& operator*() const
        {
            return *ptr;
        }
        
        const T* operator->() const
        {
            return ptr;
        }
        
        T* operator->()
        {
            return ptr;
        }
        
    private:
        T * ptr;
    };
}

#endif
