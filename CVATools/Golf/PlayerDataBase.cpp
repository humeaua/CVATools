//
//  PlayerDataBase.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 20/10/13.
//
//

#include "PlayerDataBase.h"
#include "dirent.h"
#include "Exception.h"
#include "time.h"

namespace Golf
{
    PlayerDataBase::PlayerDataBase(const std::string & cDirectoryName, DiscountType eDiscountType, const Utilities::Date::MyDate & sDate)
    {
        LoadFromDirectory(cDirectoryName, eDiscountType, sDate);
    }
    
    PlayerDataBase::~PlayerDataBase()
    {
        //for (std::size_t i = 0 ; i < sPlayers_.size() ; ++i)
        //{
        //    sPlayers_[i].~Player();
        //}
        sPlayers_.clear();
    }
    
    void PlayerDataBase::LoadFromDirectory(const std::string & cDirectoryName, DiscountType eDiscountType, const Utilities::Date::MyDate & sDate)
    {
        DIR *dir;
        struct dirent *ent;
        if ((dir = opendir (cDirectoryName.c_str())) != NULL)
        {
            /* print all the files and directories within directory */
            clock_t tic = clock();
            while ((ent = readdir (dir)) != NULL)
            {
                std::string str = ent->d_name;
                unsigned long found = str.find_last_of(".");
                std::string cLastChar = str.substr(found+1, str.size());
                if (cLastChar == "csv" || cLastChar == "CSV")
                {
                    std::cout << "Loading " << str << std::endl;
                    sPlayers_.push_back(Player());
                    sPlayers_.back().LoadFromFile(cDirectoryName + "/" + str, eDiscountType, sDate);
                }
            }
            std::cout << "Loading completed in " << (double)(clock() - tic) / CLOCKS_PER_SEC << " seconds" << std::endl;
            closedir (dir);
        }
        else
        {
            /* could not open directory */
            throw EXCEPTION("cannot open directory");
        }
    }
    
    void PlayerDataBase::ComputeRanking()
    {
        clock_t tic = clock();
        std::sort(sPlayers_.begin(), sPlayers_.end(), std::greater<Player>());
        std::cout << "Computation of ranking done in " << (double)(clock() - tic) / CLOCKS_PER_SEC << " seconds" << std::endl;
        std::cout << std::endl;
    }
    
    std::vector<Player> PlayerDataBase::GetDataBase() const
    {
        return sPlayers_;
    }
}