//
//  PlayerRanking.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 28/12/14.
//
//

#ifndef __CVATools__PlayerRanking__
#define __CVATools__PlayerRanking__

#include <iostream>
#include <vector>
#include "Date.h"

class PlayerRanking
{
protected:
    std::vector<std::pair<Utilities::Date::MyDate, double> > m_results;
    
public:
    
    std::vector<std::pair<Utilities::Date::MyDate, double> > & GetResults();
    const std::vector<std::pair<Utilities::Date::MyDate, double> > & GetResults() const;

    void AddResult(const Utilities::Date::MyDate & tournamentDate, const double & tournamentPoints);
};

#endif /* defined(__CVATools__PlayerRanking__) */
