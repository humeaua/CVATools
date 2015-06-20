//
//  main.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 10/03/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "RegressionTestLauncher.h"
#include "Exception.h"
#include <fstream>

//////////////////////////////////
//  Forward Declaration
//////////////////////////////////
int _main();
const std::string currentDateTime();

///////////////////////////////////
//  Main functions
///////////////////////////////////

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const std::string currentDateTime()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%H-%M-%S", &tstruct);
    
    return buf;
}

int _main()
{
    std::cout << "Launching tests" << std::endl;
    const std::string filename = "Test_" + currentDateTime() + ".log";
    std::fstream file(filename.c_str(), std::fstream::out);
    RegressionTestLauncher launcher(file);
    bool bSucceeded = launcher.Launch();
    
    std::cout << "Log captured in " << filename << std::endl;
    if (!bSucceeded)
    {
        std::cout << "Tests finished with errors. see output file " << filename << std::endl;
    }
    return (int)(!bSucceeded);
}

int main()
{
    try
    {
        return _main();
    }
    catch (const Utilities::MyException & excep)
    {
        std::cout << "MyException caught : " << excep.what() << std::endl;
    }
    catch (const std::exception & excep)
    {
        std::cout << "std::exception caught : " << excep.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "Unknown exception caught !" << std::endl;
    }
}