//
//  Require.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 28/12/13.
//
//

#include "Require.h"

namespace Utilities {
    
    void require(bool requirement,
                        const char* msg)
    {
        if(!requirement)
        {
            fputs(msg, stderr);
            fputs("\n", stderr);
            exit(EXIT_FAILURE);
        }
    }
    
    void requireException(bool requirement,
                                 const std::string & msg,
                                 const std::string & cFunctionName)
    {
        if (!requirement)
        {
            std::string cMsg = cFunctionName + " : " + msg;
            throw MyException(cMsg);
        }
    }
    
    void requireArgs(int argc, int args, const char* msg)
    {
        if(argc != args + 1)
        {
            fprintf(stderr, msg, args);
            fputs("\n", stderr);
            exit(EXIT_FAILURE);
        }
    }
    
    void requireMinArgs(int argc, int minArgs, const char* msg)
    {
        if(argc < minArgs + 1)
        {
            fprintf(stderr, msg, minArgs);
            fputs("\n", stderr);
            exit(EXIT_FAILURE);
        }
    }
    
    void assure(std::ifstream& in, const char* filename)
    {
        if(!in)
        {
            fprintf(stderr, "Could not open file %s\n", filename);
            exit(EXIT_FAILURE);
        }
    }
    
    void assure(std::ofstream& in, const char* filename)
    {
        if(!in)
        {
            fprintf(stderr, "Could not open file %s\n", filename);
            exit(EXIT_FAILURE);
        }
    }
    
    void assure(std::fstream& in, const char* filename)
    {
        if(!in)
        {
            fprintf(stderr, "Could not open file %s\n", filename);
            exit(EXIT_FAILURE);
        }
    }
}