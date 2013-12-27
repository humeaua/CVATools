//: :require.h
// From "Thinking in C++, Volume 2", by Bruce Eckel & Chuck Allison.
// (c) 1995-2004 MindView, Inc. All Rights Reserved.
// See source code use permissions stated in the file 'License.txt',
// distributed with the code package available at www.MindView.net.
// Test for error conditions in programs.
#ifndef Seminaire_Require_h
#define Seminaire_Require_h
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include "Exception.h"

namespace Utilities {
    
    inline void require(bool requirement,
                        const char* msg = "Requirement failed")
    {
        if(!requirement)
        {
            fputs(msg, stderr);
            fputs("\n", stderr);
            exit(EXIT_FAILURE);
        }
    }
    
    inline void requireException(bool requirement,
                                 const std::string & msg,
                                 const std::string & cFunctionName)
    {
        std::string cMsg = cFunctionName + " : " + msg;
        if (!requirement)
            throw MyException(cMsg);
    }
    
    inline void requireArgs(int argc, int args,
                            const char* msg = "Must use %d arguments")
    {
        if(argc != args + 1)
        {
            fprintf(stderr, msg, args);
            fputs("\n", stderr);
            exit(EXIT_FAILURE);
        }
    }
    
    inline void requireMinArgs(int argc, int minArgs,
                               const char* msg = "Must use at least %d arguments")
    {
        if(argc < minArgs + 1)
        {
            fprintf(stderr, msg, minArgs);
            fputs("\n", stderr);
            exit(EXIT_FAILURE);
        }
    }
    
    inline void assure(std::ifstream& in,
                       const char* filename = "")
    {
        if(!in)
        {
            fprintf(stderr, "Could not open file %s\n", filename);
            exit(EXIT_FAILURE);
        }
    }
    
    inline void assure(std::ofstream& in,
                       const char* filename = "")
    {
        if(!in)
        {
            fprintf(stderr, "Could not open file %s\n", filename);
            exit(EXIT_FAILURE);
        }
    }
    
    inline void assure(std::fstream& in,
                       const char* filename = "")
    {
        if(!in)
        {
            fprintf(stderr, "Could not open file %s\n", filename);
            exit(EXIT_FAILURE);
        }
    }
}
#endif
