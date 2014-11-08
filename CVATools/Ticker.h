//
//  Ticker.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 07/11/14.
//
//

#ifndef CVATools_Ticker_h
#define CVATools_Ticker_h

#include <iostream>
#include <sstream>

namespace Utilities
{
    template<class T>
    class Ticker
    {
        Ticker(const Ticker & );
        Ticker & operator=(const Ticker &) const;
        
        static T m_Object;
    protected:
        size_t m_Tick;
        std::string m_Name;
    public:
        Ticker(const std::string & name) : m_Name(name), m_Tick(0)
        {}
        
        ~Ticker()
        {}
        
        static T& Instance()
        {
            return m_Object;
        }
        
        void Store(const T& value)
        {
            m_Object = value;
            m_Tick++;
        }
        
        std::string Name() const
        {
            std::stringstream ss;
            ss << m_Name << "." << m_Tick;
            return ss.str();
        }
    };
    
    template<class T>
    T Ticker<T>::m_Object = T(0);
}

#endif
