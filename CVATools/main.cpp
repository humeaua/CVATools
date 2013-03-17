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
}

