//
//  PlayerDataBase.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 20/10/13.
//
//

#ifndef __CVATools__PlayerDataBase__
#define __CVATools__PlayerDataBase__

#include <iostream>
#include "Player.h"
#include <vector>

namespace Golf
{
    class PlayerDataBase
    {
    protected:
        std::vector<Player> sPlayers_;
    public:
        PlayerDataBase(const std::string & cDirectoryName);
        virtual ~PlayerDataBase();

        virtual void LoadFromDirectory(const std::string & cDirectoryName);

        virtual void ComputeRanking();
        
        virtual std::vector<Player> GetDataBase() const;
    };
}

#endif /* defined(__CVATools__PlayerDataBase__) */
