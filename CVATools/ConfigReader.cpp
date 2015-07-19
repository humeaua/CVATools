//
//  ConfigReader.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 24/05/2015.
//
//

#include "ConfigReader.h"
#include "Player.h"
#include "Holidays.h"
#include "StringUtilities.h"

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

template <>
void ConfigReader::Fill(Utilities::Holidays & holidays, const std::string &name) const
{
    // Fill the implementation of the holidays structure
    const std::string holidays_ = "HOLIDAYS";
    std::map<std::string, Utilities::Variant>::const_iterator itHolidays = m_internalMap.find(holidays_);
    
    if (itHolidays != m_internalMap.end())
    {
        const std::string holidayStr = itHolidays->second.GetString();
        const char delimHolidays = ';';
        
        std::vector<std::string> vecStr = Utilities::Split(holidayStr, delimHolidays);
        std::set<long> holidaySet;
        for (size_t i = 0 ; i < vecStr.size() ; ++i)
        {
            std::stringstream ss;
            ss << vecStr[i];
            long l;
            ss >> l;
            holidaySet.insert(l);
        }
        
        holidays = Utilities::Holidays(holidaySet);
    }
}

template<>
void ConfigReader::Fill(Utilities::Date::MyDate & date, const std::string &name) const
{
    //  not so nice implementation
    const std::string day_ = name + m_delim + "DAY";
    std::map<std::string, Utilities::Variant>::const_iterator itDay = m_internalMap.find(day_);
    if (itDay != m_internalMap.end())
    {
        date.SetDay(itDay->second.GetInt());
    }
    
    const std::string month_ = name + m_delim + "MONTH";
    std::map<std::string, Utilities::Variant>::const_iterator itMonth = m_internalMap.find(month_);
    if (itMonth != m_internalMap.end())
    {
        date.SetMonth(itMonth->second.GetInt());
    }
    
    const std::string year_ = name + m_delim + "YEAR";
    std::map<std::string, Utilities::Variant>::const_iterator itYear = m_internalMap.find(year_);
    if (itYear != m_internalMap.end())
    {
        date.SetYear(itYear->second.GetInt());
    }
}

template<>
void ConfigReader::Fill(PlayerID & playerId, const std::string & name) const
{
    const std::string lookupValue = name + m_delim + "NAME";
    std::map<std::string, Utilities::Variant>::const_iterator it = m_internalMap.find(lookupValue);
    
    const std::string lookupValueBirthDate = name + m_delim + "BIRTHDATE";
    Utilities::Date::MyDate birthDate; // not filled yet
    Fill(birthDate, lookupValueBirthDate);
    
    if (it != m_internalMap.end() && birthDate.getState() != Utilities::Date::MyDate::INVALID)
    {
        playerId = PlayerID(it->second.GetString(), birthDate);
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