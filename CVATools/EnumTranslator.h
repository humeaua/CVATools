//
//  EnumTranslator.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 17/06/2015.
//
//

#ifndef CVATools_EnumTranslator_h
#define CVATools_EnumTranslator_h

#include <map>
#include <sstream>
#include "Exception.h"

namespace Utilities
{
    template<typename ENUMT>
    class EnumTranslator
    {
        std::map<std::string, ENUMT> m_mapping;
        mutable typename std::map<std::string, ENUMT>::const_iterator m_it; // maybe better solution to avoid finding twice
        
        bool CanTranslate(const std::string & name) const
        {
            m_it = m_mapping.find(name);
            return m_it != m_mapping.end();
        }
    public:
        void Add(const std::string & name, ENUMT enumValue)
        {
            m_mapping.insert(std::make_pair(name, enumValue));
        }
        
        ENUMT Translate(const std::string & name) const
        {
            if (CanTranslate(name))
            {
                return m_it->second;
            }
            else
            {
                std::stringstream ss;
                ss << "Cannot find name : " << name << " in map";
                throw EXCEPTION(ss.str());
            }
        }
    };
}

#endif
