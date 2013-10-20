//
//  PlayerResult.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 20/10/13.
//
//

#ifndef __CVATools__PlayerResult__
#define __CVATools__PlayerResult__

#include <iostream>
#include "Date.h"

namespace Golf
{
    class PlayerResult
    {
    protected:
        std::string cTournamentName_;
        Utilities::Date::MyDate sTournamentDate_;
        double dPoint_;
    public:
        PlayerResult(const std::string & cTournamentName, const Utilities::Date::MyDate & sTournamentDate, double dPoint);
        virtual ~PlayerResult();
        
        virtual bool operator==(const PlayerResult & sRight);
        virtual bool operator<(const PlayerResult & sRight) const;
        
        virtual double GetPoint() const;
        virtual Utilities::Date::MyDate GetDate() const;
        virtual std::string GetTournamentName() const;
        
        //static PlayerResult Make(const Utilities::Date::MyDate & sTournamentDate, double dPoint);
    };
}

#endif /* defined(__CVATools__PlayerResult__) */
