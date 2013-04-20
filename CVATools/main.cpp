//
//  main.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 10/03/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <pthread.h>
#include <iostream>
#include "OrnsteinUhlenbeck.h"
#include "Print.h"
#include "SquareRoot.h"
#include "BlackScholes.h"
#include "MargrabeOptionVasicek.h"
#include <cmath>
#include <sstream>

#define NUM_THREADS 5

/*int main (int argc, const char * argv[])
{

    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}*/

/*void *PrintHello(void *threadid);
void *PrintHello(void *threadid)
{
    long tid;
    tid = (long)threadid;
    std::cout << "Hello World! Thread ID, " << tid << std::endl;
    pthread_exit(NULL);
}

int main ()
{
    pthread_t threads[NUM_THREADS];
    int rc;
    int i;
    for( i=0; i < NUM_THREADS; i++ )
    {
        std::cout << "main() : creating thread, " << i << std::endl;
        rc = pthread_create(&threads[i], NULL, 
                            PrintHello, (void *)i);
        if (rc)
        {
            std::cout << "Error:unable to create thread," << rc << std::endl;
            exit(-1);
        }
        
        //pthread_join(threads[i], NULL);
    }
    pthread_exit(NULL);
}*/

int main()
{
    std::cout << "Choose the test : " << std::endl;
    std::cout << "1- Ornstein Ulhenbeck Process" << std::endl;
    std::cout << "2- Square root process" << std::endl;
    std::cout << "3- Black Scholes process" << std::endl;
    std::cout << "4- Two Asset simulation" << std::endl;
    std::size_t iTest = 1;
    std::cin >> iTest;
    
    if (iTest == 1)
    {
        OrnsteinUhlenbeck sOU(0.05, 0.2, 0.1, 0.2);
        std::size_t iNDates = 100, iNPaths = 10;
        long long lSeed = 0;
        std::vector<double> dDates;
        double dT = 1;
        for (std::size_t iDate = 0 ; iDate < iNDates ; ++iDate)
        {
            dDates.push_back(dT * iDate / iNDates);
        }
        SimulationData sResult = sOU.simulate(dDates, iNPaths, lSeed);
        Print sPrint("/Users/alexhum49/Desktop/OrnsteinUlhenbeck.csv", false, 10);
        sPrint.PrintInFile(sResult.GetData());
    }
    else if (iTest == 2)
    {
        SquareRoot sSquareRoot(0.05, 0.2, 0.2, 0.2);
        std::size_t iNDates = 100, iNPaths = 10;
        long long lSeed = 0;
        std::vector<double> dDates;
        double dT = 10;
        for (std::size_t iDate = 0 ; iDate < iNDates ; ++iDate)
        {
            dDates.push_back(dT * iDate / iNDates);
        }
        SimulationData sResult = sSquareRoot.simulate(dDates, iNPaths, lSeed);
        Print sPrint("/Users/alexhum49/Desktop/SquareRoot.csv", false, 10);
        sPrint.PrintInFile(sResult.GetData());
    }
    else if (iTest == 3)
    {
        BlackScholes sBS(0.08, 0.4, 10);
        std::size_t iNDates = 1000, iNPaths = 10;
        long long lSeed = 1;
        std::vector<double> dDates;
        double dT = 10;
        for (std::size_t iDate = 0 ; iDate < iNDates ; ++iDate)
        {
            dDates.push_back(dT * iDate / iNDates);
        }
        SimulationData sResult = sBS.simulate(dDates, iNPaths, lSeed);
        Print sPrint("/Users/alexhum49/Desktop/BlackScholes.csv", false, 10);
        sPrint.PrintInFile(sResult.GetData());
    }
    else if (iTest == 4)
    {
        //  Definition of 3x3 correlation matrix
        Matrix sCorrelMatrix(3,3);
        sCorrelMatrix.set(0,0,1.0);
        sCorrelMatrix.set(1,1,1.0);
        sCorrelMatrix.set(2,2,1.0);
        double dRho12 = 0.2, dRho13 = 0.2, dRho23 = 0.2;
        sCorrelMatrix.set(1,0, dRho12);
        sCorrelMatrix.set(0,1, dRho12);
        sCorrelMatrix.set(2,0, dRho13);
        sCorrelMatrix.set(0,2, dRho13);
        sCorrelMatrix.set(2,1, dRho23);
        sCorrelMatrix.set(1,2, dRho23);
        Matrix sCholDec(3,3);
        //CholeskiDecomposition(sCorrelMatrix, sCholDec);
        
        //std::cout << sCholDec(0,0) << " " << sCholDec(0,1) << " " << sCholDec(0,2) << std::endl;
        //std::cout << sCholDec(1,1) << " " << sCholDec(1,1) << " " << sCholDec(1,2) << std::endl;
        //std::cout << sCholDec(2,0) << " " << sCholDec(2,1) << " " << sCholDec(2,2) << std::endl;
        
        //  Definition of vector of initial values
        DVector dInitialValues(3,0.0);
        // values for stocks are ln(S_1) and ln(S_2)
        dInitialValues[0] = log(100);
        dInitialValues[1] = log(100);
        dInitialValues[2] = 0.02; // value for initial short rate
        
        MargrabeOptionVasicek sOption(1.0, 1, sCorrelMatrix, dInitialValues, 0.05, 0.03, 0.01, 0.2, 0.3);
        
        //  Simulation Values
        std::vector<double> dDates;
        std::size_t iNDates = 100, iNPaths = 10;
        long long lSeed = 0;
        for (std::size_t i = 0 ; i < iNDates; ++i)
        {
            dDates.push_back((double)i /iNDates);
        }
        
        SimulationDataMultiDim sData = sOption.simulate(dDates, iNPaths, lSeed);
        std::map<double, std::map<std::size_t, DVector> > sDatamap = sData.GetData();
        for (std::size_t i = 0 ; i < 4 ; ++i)
        {
            std::stringstream out ;
            out << i;
            
            Print sPrint("/Users/alexhum49/Desktop/Margrabe_" + out.str() + ".csv", false, 10);
            sPrint.PrintInFile(sDatamap,i);
        }
        
        //  Test for apply function
        /*sData.Apply(exp);
        sDatamap = sData.GetData();
        DVector firstvect = sDatamap.find(0)->second.find(0)->second;
        for (std::size_t i = 0 ; i < firstvect.size() ; ++i)
        {
            std::cout << i << " " << firstvect[i] << std::endl;
        }*/
    }
}

