//
//  ConfigReader.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 24/05/2015.
//
//

#include "ConfigReader.h"
#include "Player.h"

ConfigReader::ConfigReader(const std::string & filename, const char delim) : base(filename), m_delim(delim)
{
    Read();
}

void ConfigReader::Read()
{
    do
    {
        std::vector<std::string> currentValues;
        base >> currentValues;
        if (currentValues.size() != 2)
        {
            std::stringstream ss;
            ss <<"Size should be 2 separated by '" << base.getDelim() << "'";
            throw EXCEPTION(ss.str());
        }
        m_internalMap[currentValues[0]] = Utilities::Variant(currentValues[1]);
        ++base;
    }
    while (base);
}

template<>
void ConfigReader::Fill(PlayerID & playerId, const std::string & name) const
{
    const std::string lookupValue = name + m_delim + "NAME";
    std::map<std::string, Utilities::Variant>::const_iterator it = m_internalMap.find(lookupValue);
    
    if (it != m_internalMap.end())
    {
        playerId = PlayerID(it->second.GetString());
    }
}

template<>
void ConfigReader::Fill(Player & player, const std::string & name) const
{
    const std::string prefix = name + m_delim;
    const std::string lookupPlayerID = prefix + "PlayerID";
    
    Fill((PlayerID&)player, lookupPlayerID);
    
    const std::string lookupTour = prefix + "Tour";
    std::map<std::string, Utilities::Variant>::const_iterator it = m_internalMap.find(lookupTour);
    
    if (it != m_internalMap.end())
    {
        const std::string tourStr = it->second.GetString();
        TourTypeTranslator translator;
        player.SetTourMembership(translator.Translate(tourStr));
    }
}