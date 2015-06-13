//
//  ConfigReader.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 24/05/2015.
//
//

#include "ConfigReader.h"
#include "PlayerID.h"

ConfigReader::ConfigReader(const std::string & filename) : base(filename)
{}

template<>
void ConfigReader::Fill(PlayerID & playerId, const std::string & name) const
{
    std::string lookupValue = name + ".NAME";
    std::map<std::string, Utilities::Variant>::const_iterator it = m_internalMap.find(lookupValue);
    
    if (it != m_internalMap.end())
    {
        playerId = PlayerID(it->second.GetString());
    }
}