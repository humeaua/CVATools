//
//  Tournament.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 10/10/13.
//
//

#include "Tournament.h"
#include "Exception.h"
#include <fstream>
#include "StringUtilities.h"
#include <sstream>

namespace Golf {
    
    Tournament::Tournament(const TournamentResults & mResults, const Utilities::Date::MyDate & sDate) : mResults_(mResults), sDate_(sDate)
    {}
    
    Tournament::Tournament(const std::string & cFileName)
    {
        LoadFromFile(cFileName);
    }
    
    Tournament::~Tournament()
    {
        mResults_.clear();
        sDate_.~MyDate();
    }
    
    void Tournament::Add(const Player & sPlayer, double dResult)
    {
        if (mResults_.count(sPlayer.GetName()))
        {
            mResults_[sPlayer.GetName()] = dResult;
        }
        else
        {
            mResults_.find(sPlayer.GetName())->second = dResult;
        }
    }
    
    void Tournament::Add(const std::pair<std::string, std::string> & cPlayerName, double dResult)
    {
        if (mResults_.count(cPlayerName) == 0)
        {
            mResults_[cPlayerName] = dResult;
        }
        else
        {
            mResults_.find(cPlayerName)->second = dResult;
        }
    }
    
    TournamentResults Tournament::GetResults() const
    {
        return mResults_;
    }
    
    void Tournament::LoadFromFile(const std::string &cFileName)
    {
        std::string line;
        std::ifstream myfile(cFileName.c_str(), std::ios_base::in);
        if (myfile.is_open())
        {
            while (!myfile.eof())
            {
                std::getline(myfile, line, '\r');
                // The basic format of the file is
                //  Position,FirstName,LastName,Points
                
                std::vector<std::string> cParams = Utilities::Split(line, ',');
                std::stringstream ss;
                ss << cParams.at(3);
                double dPoints = 0.0;
                ss >> dPoints;
                
                //  Add Player in Tournament results
                Add(std::make_pair(cParams.at(1), cParams.at(2)), dPoints);
            }
            myfile.close();
        }
        else
        {
            throw Utilities::MyException("Unable to open file " + cFileName);
        }
    }
    
    void Tournament::Print( std::ostream & os) const
    {
        for (TournamentResults::const_iterator it = mResults_.begin() ; it != mResults_.end() ; ++it)
        {
            os << it->first.first << " " << it->first.second << " " << it->second << std::endl;
        }
    }
}