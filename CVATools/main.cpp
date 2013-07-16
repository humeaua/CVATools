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

#include "BondPricer/BondPricer.h"
#include "GaussianKernel.h"
#include "RegressionTests.h"
#include "MuParser/muParserTest.h"
#include "Vector.h"

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
    std::cout << "0- Regression Tests" << std::endl;
    std::cout << "1- Ornstein Ulhenbeck Process" << std::endl;
    std::cout << "2- Square root process" << std::endl;
    std::cout << "3- Black Scholes process" << std::endl;
    std::cout << "4- Two Asset simulation" << std::endl;
    std::cout << "5- Bond Pricer" << std::endl;
    std::cout << "6- Yield Curve interpolation" << std::endl;
    std::cout << "7- Kernel Estimation" << std::endl;
    std::cout << "8- Business Day" << std::endl;
    std::cout << "9- Mu Parser Test" << std::endl;
    std::cout << "10- My Vector Test" << std::endl;
    std::cout << "11- Fibonacci Series" << std::endl;
    std::cout << "12- Smart pointers" << std::endl;
    std::size_t iTest = 1;
    std::cin >> iTest;
    
    if (iTest == 0)
    {
        RegressionTest_BondPricing();
        std::cout << std::endl;
        RegressionTest_TimeStatistics();
    }
    if (iTest == 1)
    {
        Finance::Processes::OrnsteinUhlenbeck sOU(0.05, 0.2, 0.1, 0.2);
        std::size_t iNDates = 100, iNPaths = 10;
        long long lSeed = 0;
        std::vector<double> dDates;
        double dT = 1;
        for (std::size_t iDate = 0 ; iDate < iNDates ; ++iDate)
        {
            dDates.push_back(dT * iDate / iNDates);
        }
        Utilities::SimulationData sResult = sOU.simulate(dDates, iNPaths, lSeed);
        Utilities::PrintC sPrint("/Users/alexhum49/Desktop/OrnsteinUlhenbeck.csv", false, 10);
        sPrint.PrintInFile(sResult.GetData());
    }
    else if (iTest == 2)
    {
        Finance::Processes::SquareRoot sSquareRoot(0.2, 0.2, 0.2, 0.2);
        std::size_t iNDates = 1000, iNPaths = 10;
        long long lSeed = 0;
        std::vector<double> dDates;
        double dT = 10;
        for (std::size_t iDate = 0 ; iDate < iNDates ; ++iDate)
        {
            dDates.push_back(dT * iDate / iNDates);
        }
        Utilities::SimulationData sResult = sSquareRoot.simulate(dDates, iNPaths, lSeed);
        Utilities::PrintC sPrint("/Users/alexhum49/Desktop/SquareRoot.csv", false, 10);
        sPrint.PrintInFile(sResult.GetData());
    }
    else if (iTest == 3)
    {
        Utilities::Processes::BlackScholes sBS(0.08, 0.4, 10);
        std::size_t iNDates = 1000, iNPaths = 10;
        long long lSeed = 1;
        std::vector<double> dDates;
        double dT = 10;
        for (std::size_t iDate = 0 ; iDate < iNDates ; ++iDate)
        {
            dDates.push_back(dT * iDate / iNDates);
        }
        Utilities::SimulationData sResult = sBS.simulate(dDates, iNPaths, lSeed);
        Utilities::PrintC sPrint("/Users/alexhum49/Desktop/BlackScholes.csv", false, 10);
        sPrint.PrintInFile(sResult.GetData());
    }
    else if (iTest == 4)
    {
        //  Definition of 3x3 correlation matrix
        Utilities::Matrix sCorrelMatrix(3,3);
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
        Utilities::Matrix sCholDec(3,3);
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
        
        Finance::Option::MargrabeOptionVasicek sOption(1.0, 1, sCorrelMatrix, dInitialValues, 0.05, 0.03, 0.01, 0.2, 0.3);
        
        //  Simulation Values
        std::vector<double> dDates;
        std::size_t iNDates = 100, iNPaths = 10;
        long long lSeed = 0;
        for (std::size_t i = 0 ; i < iNDates; ++i)
        {
            dDates.push_back((double)i /iNDates);
        }
        
        Utilities::SimulationDataMultiDim sData = sOption.simulate(dDates, iNPaths, lSeed);
        std::map<double, std::map<std::size_t, DVector> > sDatamap = sData.GetData();
        for (std::size_t i = 0 ; i < 4 ; ++i)
        {
            std::stringstream out ;
            out << i;
            
            Utilities::PrintC sPrint("/Users/alexhum49/Desktop/Margrabe_" + out.str() + ".csv", false, 10);
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
    else if (iTest == 5)
    {
        // Yield curve as of 10th May, 2013
        //          1 Mo	3 Mo	6 Mo	1 Yr	2 Yr	3 Yr	5 Yr	7 Yr	10 Yr	20 Yr	30 Yr
        // 05/10/13	0.02	0.04	0.08	0.11	0.26	0.38	0.82	1.28	1.90	2.70	3.10
        std::vector<std::pair<double, double> > dYC;
        dYC.push_back(std::make_pair(1.0 / 12, 0.0002));
        dYC.push_back(std::make_pair(3.0 / 12, 0.0004));
        dYC.push_back(std::make_pair(6.0 / 12, 0.0008));
        dYC.push_back(std::make_pair(1.0, 0.0011));
        dYC.push_back(std::make_pair(2.0, 0.0026));
        dYC.push_back(std::make_pair(3.0, 0.0038));
        dYC.push_back(std::make_pair(5.0, 0.0082));
        dYC.push_back(std::make_pair(7.0, 0.0128));
        dYC.push_back(std::make_pair(10.0, 0.0190));
        dYC.push_back(std::make_pair(20.0, 0.0270));
        dYC.push_back(std::make_pair(30.0, 0.0310));

        Utilities::Date::MyDate sStart(11,05,2014), sEnd(11,05,2034), sToday;
        Finance::Base::YieldCurve sYieldCurve(sToday, "USD", "USD_YC_10_05_2013", dYC, Utilities::Interp::LIN);
        
        Finance::Base::MyBasis eBasis = Finance::Base::BONDBASIS;
        Finance::Base::MyFrequency eFrequency = Finance::Base::MyFrequencyAnnual;
        double dNotional = 1.;
        
        std::vector<double> dCoupons(20, 0.01);
        bool bIsFixedRate = true;
        
        Finance::Pricers::BondPricer sBondPricer(sToday, sStart, sEnd, sYieldCurve, eBasis, eFrequency, dCoupons, dNotional, bIsFixedRate);
        double dBondPrice = sBondPricer.Price();
        std::cout << "Bond Pricer : " << dBondPrice << std::endl;
        std::cout << "Yield : " << sBondPricer.PriceToYield(dBondPrice) << std::endl;
        std::cout << "I-Spread : " << sBondPricer.I_Spread(dBondPrice) << std::endl;
        std::cout << "Z-Spread : " << sBondPricer.Z_Spread(dBondPrice) << std::endl;
        std::cout << "Z-Spread (2% margin) : " << sBondPricer.Z_Spread(dBondPrice * 1.02) << std::endl;
                
        /*
         Regression test
         Bond Pricer : 0.733378
         Yield : 0.0259757
         I-Spread : -0.00125763
         Z-Spread : -0.000419156
         Z-Spread (2% margin) : -0.0015014
         */

        std::cout << "Good Bye !" << std::endl;
    }
    else if (iTest == 6)
    {
        // Yield curve as of 10th May, 2013
        //          1 Mo	3 Mo	6 Mo	1 Yr	2 Yr	3 Yr	5 Yr	7 Yr	10 Yr	20 Yr	30 Yr
        // 05/10/13	0.02	0.04	0.08	0.11	0.26	0.38	0.82	1.28	1.90	2.70	3.10
        std::vector<std::pair<double, double> > dYC;
        dYC.push_back(std::make_pair(1.0 / 12, 0.0002));
        dYC.push_back(std::make_pair(3.0 / 12, 0.0004));
        dYC.push_back(std::make_pair(6.0 / 12, 0.0008));
        dYC.push_back(std::make_pair(1.0, 0.0011));
        dYC.push_back(std::make_pair(2.0, 0.0026));
        dYC.push_back(std::make_pair(3.0, 0.0038));
        dYC.push_back(std::make_pair(5.0, 0.0082));
        dYC.push_back(std::make_pair(7.0, 0.0128));
        dYC.push_back(std::make_pair(10.0, 0.0190));
        dYC.push_back(std::make_pair(20.0, 0.0270));
        dYC.push_back(std::make_pair(30.0, 0.0310));
        
        Finance::Base::YieldCurve sYieldCurve(Utilities::Date::MyDate(), "USD", "USD_YC_10_05_2013", dYC, Utilities::Interp::LIN);
        
        for (std::size_t i = 0 ; i < 400 ; ++i)
        {
            double dT = (double)i / 10.0;
            std::cout << dT << ";" << sYieldCurve.YC(dT) << std::endl;
        }
    }
    else if (iTest == 7)
    {
        try
        {
            std::vector<std::pair<double, double> > dXY;
            for (std::size_t i = 0 ; i < 100 ; ++i)
            {
                dXY.push_back(std::make_pair(i / 10.0, i / 10.0));
            }
            Maths::GaussianKernel sGaussianKernel(0.1, 1.0e-7);
            
            for (double x = 0 ; x < 11 ; x += 0.01)
            {
                std::cout << x << ";" << sGaussianKernel.Estimate(dXY, x) << std::endl;
            }
            
        }
        catch (std::exception & e)
        {
            std::cout << "Error : " << e.what() << std::endl;
        }
        
    }
    else if (iTest == 8)
    {
        Utilities::Date::MyDate sToday;
        Utilities::Date::MyDate sNextBD = sToday.NextBusinessDay(), sPrevBD = sToday.PreviousBusinessDay();
        
        std::tm Today = sToday.Totm();
        
        std::cout << "WeekDay : " << Today.tm_wday << std::endl;
        
        std::cout << "Today " << std::endl;
        sToday.Print();
        std::cout << "Next Business Day" << std::endl;
        sNextBD.Print();
        std::cout << "Previous Business Day" << std::endl;
        sPrevBD.Print();
    }
    else if (iTest == 9)
    {
        mu::Test::ParserTester sParserTester;
        sParserTester.Run();
    }
    else if (iTest == 10)
    {
        Utilities::MyVector<double> vect0(10,0), vect1(10,1), vectAdd = vect0 + vect1, vectSubs = vect0 - vect1, vectMult = vect0 * vect1, vectDiv = vect0 / vect1;
        std::cout << "Addition" << std::endl;
        for (std::size_t i = 0 ; i < vectAdd.size() ; ++i)
        {
            std::cout << vectAdd[i] << std::endl;
        }
        std::cout << "Substraction" << std::endl;
        for (std::size_t i = 0 ; i < vectSubs.size() ; ++i)
        {
            std::cout << vectSubs[i] << std::endl;
        }
        std::cout << "Multiplication" << std::endl;
        for (std::size_t i = 0 ; i < vectMult.size() ; ++i)
        {
            std::cout << vectMult[i] << std::endl;
        }
        std::cout << "Division" << std::endl;
        for (std::size_t i = 0 ; i < vectDiv.size() ; ++i)
        {
            std::cout << vectDiv[i] << std::endl;
        }
        
        Utilities::MyVector<double> vect0Add = vect0 + 1.0;
        std::cout << "Addition" << std::endl;
        for (std::size_t i = 0 ; i < vect0Add.size() ; ++i)
        {
            std::cout << vect0Add[i] << std::endl;
        }
    }
    else if (iTest == 11)
    {
        // Fibonacci series
        std::cout << "Enter n : " << std::endl;
        std::size_t n = 0;
        std::cin >> n;
        
        if (n == 0 || n == 1)
        {
            std::cout << "nth Element of Fibonacci series is : 1 " << std::endl;
        }
        else
        {
            std::size_t iNOld = 1, iNVeryOld = 1, iTemp;
            for (std::size_t i = 0 ; i < n - 1; i++)
            {
                iTemp = iNOld;
                iNOld += iNVeryOld;
                iNVeryOld = iTemp;
            }
            
            std::cout << "nth Element of Fibonacci series is : " << iNOld << std::endl;
        }
    }
    else if (iTest == 12)
    {
        std::auto_ptr<Utilities::Date::MyDate> pDate(new Utilities::Date::MyDate());
        
        std::cout << "Day : " << pDate->GetDay() << std::endl;
        std::cout << "Month : " << pDate->GetMonth() << std::endl;
        std::cout << "Year : " << pDate->GetYear() << std::endl;
    }
}