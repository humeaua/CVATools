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
    Player::Player() : dTotalPoints_(0.0), iNTournamentsPlayed_(0)
    {}
    
    Player::Player(const std::string & cFirstName, const std::string & cLastName) : cFirstName_(cFirstName), cLastName_(cLastName), dTotalPoints_(0.0), iNTournamentsPlayed_(0)
    {}
    
    Player::Player(const std::string & cCSVFile) : dTotalPoints_(0.0), iNTournamentsPlayed_(0)
    {
        LoadFromFile(cCSVFile);
    }
    
    Player::~Player()
    {}
    
    void Player::LoadFromFile(const std::string cFileName, DiscountType eDiscountType, const Utilities::Date::MyDate & sDate)
    {
        //  implementation to come because the file format is not decided yet
        std::string line;
        std::ifstream myfile(cFileName.c_str(), std::ios_base::in);
        if (myfile.is_open())
        {
            // Get the player name
            //  The player name should be the filename : path/FirstName_LastName.csv
            std::vector<std::string> cNames = Utilities::Split(cFileName, '/');
            std::vector<std::string> cNames0 = Utilities::Split(cNames.back(), '.');
            std::vector<std::string> cNames1 = Utilities::Split(cNames0.front(), '_');
            if (cNames1.size() == 2)
            {
                cFirstName_ = cNames1.front();
                cLastName_  = cNames1.back();
            }
            else
            {
                throw Utilities::MyException("Player::LoadFromFile : File name is not correct");
            }
            
            // Read the tournaments
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
                std::string cTournamentName = cParams.at(0) + cParams.at(2);
                mResults_.insert(PlayerResult(cTournamentName, sTournamentDate, dPoints));//(sTournamentDate, dPoints);
            }
            myfile.close();
            
            // Compute the total number of points 
            ComputeTotalPoints(eDiscountType, sDate);
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
    
    void Player::ComputeTotalPoints(DiscountType eDiscountType, const Utilities::Date::MyDate & sObservationDate)
    {
        Utilities::Interp::InterExtrapolation1D sDiscountCurve = OfficialWorldGolfRankings::GetDiscountCurve(eDiscountType);
        for (std::set<PlayerResult>::iterator it = mResults_.begin() ; it != mResults_.end() ; ++it)
        {
            Utilities::Date::MyDate sTournamentDate = it->GetDate();
            double dTimeDiff = sTournamentDate.Diff(sObservationDate);
            dTotalPoints_ += it->GetPoint() * sDiscountCurve.Interp1D(dTimeDiff);
            iNTournamentsPlayed_ ++;
        }
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
            os << it->GetTournamentName() << " - " << sDate.GetDay() << "/" << sDate.GetMonth() << "/" << sDate.GetYear() << " : " << it->GetPoint() << std::endl;
        }
    }
    
    void Player::PrintName(std::ostream &os) const
    {
        os << cFirstName_ << " " << cLastName_ << " : " << Average() << std::endl;
    }
    
    bool Player::operator<(const Golf::Player &sRight) const
    {
        return Average() < sRight.Average();
    }
    
    bool Player::operator>(const Golf::Player &sRight) const
    {
        return Average() > sRight.Average();
    }
}