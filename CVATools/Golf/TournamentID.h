//
//  TournamentID.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 14/12/14.
//
//

#ifndef __CVATools__TournamentID__
#define __CVATools__TournamentID__

#include <iostream>
#include "Date.h"

class TournamentID
{
protected:
    std::string m_tournamentName;
    Utilities::Date::MyDate m_tournamentDate;
    
public:
    TournamentID(const std::string & tournamentName, const Utilities::Date::MyDate & tournamentDate);
    
    virtual const std::string & TournamentName() const;
    virtual std::string & TournamentName();
    
    virtual const Utilities::Date::MyDate & TournamentDate() const;
    virtual Utilities::Date::MyDate & TournamentDate();
};

#endif /* defined(__CVATools__TournamentID__) */
