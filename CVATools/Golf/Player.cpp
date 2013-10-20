//
//  Player.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 10/10/13.
//
//

#include "Player.h"
#include "Exception.h"
#include <fstream>
#include "StringUtilities.h"
#include <sstream>
#include <cmath>

namespace Golf
{
    PlayerResult::PlayerResult(const Utilities::Date::MyDate & sTournamentDate, double dPoint): sTournamentDate_(sTournamentDate), dPoint_(dPoint)
    {}
    
    PlayerResult::~PlayerResult()
    {
        sTournamentDate_.~MyDate();
    }
    
    PlayerResult MakePlayer(const Utilities::Date::MyDate &sTournamentDate, double dPoint)
    {
        PlayerResult sPlayerResult(sTournamentDate, dPoint);
        
        return sPlayerResult;
    }
    
    bool PlayerResult::operator==(const Golf::PlayerResult &sRight)
    {
        return fabs(sRight.dPoint_ - dPoint_) < 0.001 && sRight.sTournamentDate_ == sTournamentDate_;
    }
    
    bool PlayerResult::operator<(const Golf::PlayerResult &sRight) const
    {
        return sTournamentDate_ < sRight.sTournamentDate_;
    }
    
    Utilities::Date::MyDate PlayerResult::GetDate() const
    {
        return sTournamentDate_;
    }
    
    double PlayerResult::GetPoint() const
    {
        return dPoint_;
    }
    
    Player::Player(const std::string & cFirstName, const std::string & cLastName) : cFirstName_(cFirstName), cLastName_(cLastName)
    {}
    
    Player::Player(const std::string & cCSVFile)
    {
        LoadFromFile(cCSVFile);
    }
    
    Player::~Player()
    {
        cFirstName_.~basic_string();
        cLastName_.~basic_string();
    }
    
    void Player::LoadFromFile(const std::string cFileName)
    {
        //  implementation to come because the file format is not decided yet
        std::string line;
        std::ifstream myfile(cFileName.c_str(), std::ios_base::in);
        if (myfile.is_open())
        {
            while (!myfile.eof())
            {
                std::getline(myfile, line, '\r');
                // The basic format of the file is
                //  Tournament, Week, Year, Position, Points
                
                std::vector<std::string> cParams = Utilities::Split(line, ';');
                std::stringstream ss, ss1, ss2;
                ss << cParams.at(4);
                double dPoints = 0.0;
                ss >> dPoints;
                
                int iYear = 0, iWeek = 0;
                ss1 << cParams.at(1);
                ss1 >> iWeek;
                ss2 << cParams.at(2);
                ss2 >> iYear;
                
                Utilities::Date::MyDate sTournamentDate(1,1,iYear);
                sTournamentDate.Add(iWeek - 1, Utilities::Date::WEEK);
                
                //  Add Player in Tournament results
                //Add(std::make_pair(cParams.at(1), cParams.at(2)), dPoints);
                std::string cTournamentName = cParams.at(0) + " " + cParams.at(2);
                mResults_.insert(PlayerResult(sTournamentDate, dPoints));//(sTournamentDate, dPoints);
            }
            myfile.close();
        }
        else
        {
            throw Utilities::MyException("Unable to open file " + cFileName);
        }
    }
    
    double Player::Average() const
    {
        return iNTournamentsPlayed_ < 40 ? dTotalPoints_ / 40.0 : iNTournamentsPlayed_ > 52 ? dTotalPoints_ / 52 : dTotalPoints_ / iNTournamentsPlayed_;
    }
    
    std::pair<std::string, std::string> Player::GetName() const
    {
        return std::make_pair(cFirstName_, cLastName_);
    }
    
    bool Player::HasPlayed(const Golf::Tournament &sTournament) const
    {
        return sTournament.GetResults().count(std::make_pair(cFirstName_, cLastName_)) != 0;
    }
    
    void Player::Print(std::ostream &os) const
    {
        os << "Player : " << cFirstName_ << " " << cLastName_ << std::endl;
        os << std::endl;
        for (std::set<PlayerResult>::iterator it = mResults_.begin() ; it != mResults_.end() ; ++it)
        {
            Utilities::Date::MyDate sDate = it->GetDate();
            os << sDate.GetDay() << "/" << sDate.GetMonth() << "/" << sDate.GetYear() << " : " << it->GetPoint() << std::endl;
        }
    }
}