//
//  main.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 10/03/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "RegressionTestLauncher.h"
#include "Exception.h"

//////////////////////////////////
//  Forward Declaration
//////////////////////////////////
int _main();

///////////////////////////////////
//  Main functions
///////////////////////////////////

int _main()
{
    RegressionTestLauncher launcher(std::cout);
    bool bSucceeded = launcher.Launch();
    std::cout << "Regresssion Tests : " ;
    
    if (bSucceeded)
    {
        std::cout << "SUCCEEDED" << std::endl;
    }
    else
    {
        std::cout << "FAILED" << std::endl;
    }
    return 0;
}

int main()
{
    try
    {
        _main();
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
    std::cout << "Done !" << std::endl;
    return 0; 
}