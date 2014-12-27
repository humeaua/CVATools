//
//  main.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 10/03/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "MargrabeOptionVasicek.h"
#include "RegressionTests.h"
#include "MuParser/muParserTest.h"
#include "VectorUtilities.h"

#include "Printcpp.h"

#include <set>

//////////////////////////////////
//  Forward Declaration
//////////////////////////////////
int _main();
void DisplayChoices(size_t & iTest);

///////////////////////////////////
//  Main functions
///////////////////////////////////
void DisplayChoices(size_t & iTest)
{
    std::cout << "Choose the test : " << std::endl;
    std::cout << "0- Regression Tests" << std::endl;
    std::cout << "4- Two Asset simulation" << std::endl;
    std::cin >> iTest;
}

int _main()
{
    std::size_t iTest = -1;
    DisplayChoices(iTest);
    
    if (iTest == 0)
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
    }
    else if (iTest == 4)
    {
        //  Definition of 3x3 correlation matrix
        Utilities::Matrix<double> sCorrelMatrix(3,3);
        sCorrelMatrix(0,0) = 1.0;
        sCorrelMatrix(1,1) = 1.0;
        sCorrelMatrix(2,2) = 1.0;
        double dRho12 = 0.2, dRho13 = 0.2, dRho23 = 0.2;
        sCorrelMatrix(1,0) = dRho12;
        sCorrelMatrix(0,1) = dRho12;
        sCorrelMatrix(2,0) = dRho13;
        sCorrelMatrix(0,2) = dRho13;
        sCorrelMatrix(2,1) = dRho23;
        sCorrelMatrix(1,2) = dRho23;
        Utilities::Matrix<double> sCholDec(3,3);
        //CholeskiDecomposition(sCorrelMatrix, sCholDec);
        
        //std::cout << sCholDec(0,0) << " " << sCholDec(0,1) << " " << sCholDec(0,2) << std::endl;
        //std::cout << sCholDec(1,1) << " " << sCholDec(1,1) << " " << sCholDec(1,2) << std::endl;
        //std::cout << sCholDec(2,0) << " " << sCholDec(2,1) << " " << sCholDec(2,2) << std::endl;
        
        //  Definition of vector of initial values
        Utilities::MyVector<double> dInitialValues(3,0.0);
        // values for stocks are ln(S_1) and ln(S_2)
        dInitialValues.at(0) = log(100);
        dInitialValues.at(1) = log(100);
        dInitialValues.at(2) = 0.02; // value for initial short rate
        long long lSeed = 0;
        
        Finance::Option::MargrabeOptionVasicek sOption(1.0, 1, sCorrelMatrix, dInitialValues, 0.05, 0.03, 0.01, 0.2, 0.3, lSeed);
        
        //  Simulation Values
        std::vector<double> dDates;
        std::size_t iNDates = 100, iNPaths = 10;
        for (std::size_t i = 0 ; i < iNDates; ++i)
        {
            dDates.push_back(static_cast<double>(i) /iNDates);
        }
        
        Utilities::SimulationDataMultiDim sData = sOption.simulate(dDates, iNPaths);
        std::map<double, std::map<std::size_t, std::vector<double> > > sDatamap = sData.GetData();
        for (std::size_t i = 0 ; i < 4 ; ++i)
        {
            std::stringstream out ;
            out << i;
            
            Utilities::PrintCpp sPrint("/Users/alexhum49/Documents/Workspace/CVA/CVATools/Output/Margrabe_" + out.str() + ".csv", false, 10);
            sPrint.PrintInFile(sDatamap,i);
        }
        
        //  Test for apply function
        //sData.Apply(exp);
        //sDatamap = sData.GetData();
        //std::vector<double> firstvect = sDatamap.find(0)->second.find(0)->second;
        //for (std::size_t i = 0 ; i < firstvect.size() ; ++i)
        //{
        //    std::cout << i << " " << firstvect[i] << std::endl;
        //}
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