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
#include "VectorUtilities.h"

#include <tr1/memory>
#include "PayoffVanillaOption.h"
#include "BlackScholes.h"
#include "PayoffLinearization.h"
#include "MathFunctions.h"
#include "Printcpp.h"
#include "Sobol.h"
#include <set>
#include <functional>
#include "StochCorrel.h"
#include <stack>
#include "OfficialWorldGolfRankings.h"
#include "Tournament.h"
#include "dirent.h"
#include "PlayerDataBase.h"
//#include "HTTPFetcher.h"
#include "linalg.h"
#include "VectorUtilities.h"

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

//////////////////////////////////
//  Forward Declaration
//////////////////////////////////
int _main();
void DisplayChoices(size_t & iTest);

//////////////////////////////////
//  Class declaration
//////////////////////////////////
class FileWriter : public std::vector<std::string>
{
public:
    FileWriter(const std::vector<std::string> & stringvect) : std::vector<std::string>(stringvect)
    {}
    
    virtual void Write(std::ostream & out = std::cout) const
    {
        for (std::vector<std::string>::const_iterator it = begin(); it != end(); ++it)
        {
            out << *it << std::endl;
        }
    }
};

///////////////////////////////////
//  Main functions
///////////////////////////////////
void DisplayChoices(size_t & iTest)
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
    std::cout << "13- Payoff Linearization" << std::endl;
    std::cout << "14- Cracking the coding interview" << std::endl;
    std::cout << "15- Debye Function" << std::endl;
    std::cout << "16- Sobol Sequences" << std::endl;
    std::cout << "17- Thinking in C++" << std::endl;
    std::cout << "18- Stochastic Correlation" << std::endl;
    std::cout << "19- Random number one step generation" << std::endl;
    std::cout << "20- FileWriter" << std::endl;
    std::cout << "21- Map" << std::endl;
    std::cout << "22- Golf" << std::endl;
    std::cout << "23- Tournament writer" << std::endl;
    std::cout << "24- Player Reader" << std::endl;
    std::cout << "25- Directory reader" << std::endl;
    std::cout << "26- Player Data Base" << std::endl;
    std::cout << "27- HTTP Fetcher" << std::endl;
    std::cout << "28- Exo DM louis matrices" << std::endl;
    std::cout << "29- Alglib testing" << std::endl;
    std::cout << "30- Exception Testing" << std::endl;
    std::cout << "31- Smile Interpolation by splines" << std::endl;
   std::cin >> iTest;
}

int _main()
{
    std::size_t iTest = 1;
    DisplayChoices(iTest);
    
    if (iTest == 0)
    {
        RegressionTest_BondPricing();
        std::cout << std::endl;
        RegressionTest_TimeStatistics();
        std::cout << std::endl;
        RegressionTest_PayoffLinearization();
        std::cout << std::endl;
        RegressionTest_Interpolation();
        std::cout << std::endl;
        RegressionTest_VolatilitySurfaceInterpolation();
        std::cout << std::endl;
        RegressionTest_ProcessPathSimulation();
        std::cout << std::endl;
    }
    if (iTest == 1)
    {
        long long lSeed = 0;
        Finance::Processes::OrnsteinUhlenbeck sOU(0.05, 0.2, 0.1, 0.2, lSeed);
        std::size_t iNDates = 100, iNPaths = 10;
        std::vector<double> dDates;
        double dT = 1;
        for (std::size_t iDate = 0 ; iDate < iNDates ; ++iDate)
        {
            dDates.push_back(dT * iDate / iNDates);
        }
        Utilities::SimulationData sResult = sOU.simulate(dDates, iNPaths);
        Utilities::PrintCpp sPrint("/Users/alexhum49/Documents/Workspace/CVA/CVATools/Output/OrnsteinUlhenbeck.csv", false, 10);
        sPrint.PrintInFile(sResult.GetData());
    }
    else if (iTest == 2)
    {
        long long lSeed = 0;
        Finance::Processes::SquareRoot sSquareRoot(0.2, 0.2, 0.2, 0.2, lSeed);
        std::size_t iNDates = 1000, iNPaths = 10;
        std::vector<double> dDates;
        double dT = 10;
        for (std::size_t iDate = 0 ; iDate < iNDates ; ++iDate)
        {
            dDates.push_back(dT * iDate / iNDates);
        }
        Utilities::SimulationData sResult = sSquareRoot.simulate(dDates, iNPaths);
        Utilities::PrintCpp sPrint("/Users/alexhum49/Documents/Workspace/CVA/CVATools/Output/SquareRoot.csv", false, 10);
        sPrint.PrintInFile(sResult.GetData());
    }
    else if (iTest == 3)
    {
        try
        {
            long long lSeed = 1;
            Finance::Processes::BlackScholes sBS(0.08, 0.4, 10, lSeed);
            std::size_t iNDates = 10, iNPaths = 10;
            std::vector<double> dDates;
            double dT = 10;
            for (std::size_t iDate = 0 ; iDate <= iNDates ; ++iDate)
            {
                dDates.push_back(dT * iDate / iNDates);
            }
            Utilities::SimulationData sResult = sBS.simulate(dDates, iNPaths);
            Utilities::PrintCpp sPrint("/Users/alexhum49/Documents/Workspace/CVA/CVATools/Output/BlackScholes.csv", false, 10);
            sPrint.PrintInFile(sResult.GetData());
        }
        catch (std::exception & e)
        {
            std::cout << "Exception caught : " << e.what() << std::endl;
        }
        catch (...)
        {
            std::cout << "Unknown exception caught!" << std::endl;
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
            dDates.push_back((double)i /iNDates);
        }
        
        Utilities::SimulationDataMultiDim sData = sOption.simulate(dDates, iNPaths);
        std::map<double, std::map<std::size_t, DVector> > sDatamap = sData.GetData();
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
        //DVector firstvect = sDatamap.find(0)->second.find(0)->second;
        //for (std::size_t i = 0 ; i < firstvect.size() ; ++i)
        //{
        //    std::cout << i << " " << firstvect[i] << std::endl;
        //}
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
        Finance::Base::YieldCurve sYieldCurve(sToday, "USD", "USD_YC_10_05_2013", Utilities::GetPairOfVectorFromVectorOfPair(dYC));
        
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
                
        
         //Regression test
         //Bond Pricer : 0.733378
         //Yield : 0.0259757
         //I-Spread : -0.00125763
         //Z-Spread : -0.000419156
         //Z-Spread (2% margin) : -0.0015014

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
        
        Finance::Base::YieldCurve sYieldCurve(Utilities::Date::MyDate(), "USD", "USD_YC_10_05_2013", Utilities::GetPairOfVectorFromVectorOfPair(dYC));
        
        for (std::size_t i = 0 ; i < 400 ; ++i)
        {
            double dT = (double)i / 10.0;
            std::cout << dT << ";" << sYieldCurve(dT) << std::endl;
        }
    }
    else if (iTest == 7)
    {
        try
        {
            std::vector<std::pair<double, double> > dXY;
            for (std::size_t i = 0 ; i < 10 ; ++i)
            {
                dXY.push_back(std::make_pair(i, i));
            }
            //  Bandwidth seems to have a floor effect : the estimated function is a piecewise constant function now with point to spaced
            Maths::GaussianKernel sGaussianKernel(0.1, 1.0e-9);
            
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
            std::cout << vectAdd.at(i) << std::endl;
        }
        std::cout << "Substraction" << std::endl;
        for (std::size_t i = 0 ; i < vectSubs.size() ; ++i)
        {
            std::cout << vectSubs.at(i) << std::endl;
        }
        std::cout << "Multiplication" << std::endl;
        for (std::size_t i = 0 ; i < vectMult.size() ; ++i)
        {
            std::cout << vectMult.at(i) << std::endl;
        }
        std::cout << "Division" << std::endl;
        for (std::size_t i = 0 ; i < vectDiv.size() ; ++i)
        {
            std::cout << vectDiv.at(i) << std::endl;
        }
        
        Utilities::MyVector<double> vect0Add = vect0 + 1.0;
        std::cout << "Addition" << std::endl;
        for (std::size_t i = 0 ; i < vect0Add.size() ; ++i)
        {
            std::cout << vect0Add.at(i) << std::endl;
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
        
        std::cout << "Date" << std::endl;
        std::cout << "Day : " << pDate->GetDay() << std::endl;
        std::cout << "Month : " << pDate->GetMonth() << std::endl;
        std::cout << "Year : " << pDate->GetYear() << std::endl;
        std::cout << std::endl;
        
        std::tr1::shared_ptr<Utilities::Date::MyDate> pDate0(new Utilities::Date::MyDate());
        
        std::cout << "Date0" << std::endl;
        std::cout << "Day : " << pDate0->GetDay() << std::endl;
        std::cout << "Month : " << pDate0->GetMonth() << std::endl;
        std::cout << "Year : " << pDate0->GetYear() << std::endl;
        std::cout << std::endl;
        
        std::tr1::shared_ptr<Utilities::Date::MyDate> pDate1(new Utilities::Date::MyDate(20,7,2012));
        pDate0.swap(pDate1);
        
        std::cout << "Date0" << std::endl;
        std::cout << "Day : " << pDate0->GetDay() << std::endl;
        std::cout << "Month : " << pDate0->GetMonth() << std::endl;
        std::cout << "Year : " << pDate0->GetYear() << std::endl;
        std::cout << std::endl;
    }
    else if (iTest == 13)
    {
        // Payoff Linearisation
        long long lSeed = 0;
        Finance::Payoff::PayoffVanillaOption sPayoff(1.0, Finance::Payoff::CALL);
        Finance::Processes::BlackScholes sBlackScholes(0.0, 0.4, 1.0, lSeed);
        
        Maths::PayoffLinearization sPayoffLinearization(1000);
        
        double dDates[2] = {0.0, 1.0};
        std::vector<double> dSimulationsDates(dDates, dDates + 2);
    
        std::pair<double, double> dRegCoefs = sPayoffLinearization.Linearise(sBlackScholes, sPayoff, dSimulationsDates);
        
        std::cout << "Cst : " << dRegCoefs.first << std::endl;
        std::cout << "Coef Stock : " << dRegCoefs.second << std::endl;
        
        //std::cout << "R2 : " << sPayoffLinearization.Computer2() << std::endl;
    }
    else if (iTest == 14)
    {
        //  cracking the coding interview
        std::string cString = "ALEXANDRE";
        cString.append(" HUMEAU");
        std::cout << cString << std::endl;
        //char[] cCharArray = cString.to
    }
    else if (iTest == 15)
    {
        // Debye function testing for Frank copula
        std::size_t k = 1;
        std::vector<std::pair<double, double> > dXY;
        try
        {
            for (double x = 0.01 ; x < 10.0 ; x += 0.01)
            {
                dXY.push_back(std::make_pair(x, Maths::DebyeFunction(x, k)));
            }
        }
        catch(Utilities::MyException & e)
        {
            std::cout << "Exception caught" << e.what() << std::endl;
        }
        Utilities::PrintCpp sPrintCPP("/Users/alexhum49/Documents/Workspace/CVA/CVATools/Output/DebyeFunction.csv", false, 10);
        sPrintCPP.PrintInFile(dXY);
    }
    else if (iTest == 16)
    {
        //  Generation of quasi-random number using sobol sequences
        int dim_num = 1110;
        long long int seed = 110;
        std::vector<double> quasi1(dim_num, 0.0), quasi2(dim_num, 0.0);
        i8_sobol (dim_num,&seed,Utilities::GetPointer(quasi1));
        i8_sobol(dim_num, &seed, Utilities::GetPointer(quasi2));
        
        std::vector<std::pair<double, double> > dPairOfRandomNumber;
        for (std::size_t i = 0 ; i < dim_num ; ++i)
        {
            dPairOfRandomNumber.push_back(std::make_pair(quasi1[i], quasi2[i]));
        }
        Utilities::PrintCpp sPrintCPP("/Users/alexhum49/Documents/Workspace/CVA/CVATools/Output/SobolSequence.csv", false, 10);
        sPrintCPP.PrintInFile(dPairOfRandomNumber);
    }
    else if (iTest == 17)
    {
        // Thinking in C++ - Volume 2
        /*std::vector<int> iVect(10, 2);
        std::copy(iVect.begin(), iVect.end(), std::ostream_iterator<int>(std::cout, "\n"));
        
        std::transform(iVect.begin(), iVect.end(), iVect.begin(), bind2nd(std::multiplies<int>(), 10));
        std::copy(iVect.begin(), iVect.end(), std::ostream_iterator<int>(std::cout, "\n"));
        
        iVect.at(0)++;
        std::cout << iVect.at(0) << std::endl;
        
        int * bli = iVect.data();
        std::cout << "Print of bli" << std::endl;
        std::copy(bli, bli + iVect.size(), std::ostream_iterator<int>(std::cout, ","));
        
        std::cout << std::endl;
        iVect.erase( std::remove_if(iVect.begin(), iVect.end(), bind2nd(std::greater_equal<int>(), 20) ), iVect.end() );
        std::copy(bli, bli + iVect.size(), std::ostream_iterator<int>(std::cout, ","));*/
        std::set<double> doubleset;
        for (std::size_t i = 0 ; i < 10 ; ++i)
            for (double j = 0.0 ; j < 10.0 ; j+= 1.0)
                doubleset.insert(j);
        
        std::copy(doubleset.begin(), doubleset.end(), std::ostream_iterator<double>(std::cout, "\n"));
        
        std::cout << std::endl;
        std::cout << "Stack" << std::endl;
        std::stack<double> doublestack;
        for (std::size_t i = 0 ; i < 10 ; ++i)
            for (double j = 0.0 ; j < 10.0 ; j+= 1.0)
                doublestack.push(i*j);
        
        while (!doublestack.empty())
        {
            std::cout << doublestack.top() << std::endl;
            doublestack.pop();
            doublestack.pop();
        }
        
        std::cout << std::endl;
    }
    else if (iTest == 18)
    {
        long long lSeed = 0;
        Finance::Processes::StochCorrel sStochCorrel(1.0, 1.0, 0.2, 0.5, lSeed);
        std::size_t iNDates = 500, iNPaths = 10;
        std::vector<double> dDates;
        double dT = 10;
        for (std::size_t iDate = 0 ; iDate < iNDates ; ++iDate)
        {
            dDates.push_back(dT * iDate / iNDates);
        }
        Utilities::SimulationData sResult = sStochCorrel.simulate(dDates, iNPaths);
        Utilities::PrintCpp sPrint("/Users/alexhum49/Documents/Workspace/CVA/CVATools/Output/StochCorrel.csv", false, 10);
        sPrint.PrintInFile(sResult.GetData());
    }
    else if (iTest == 19)
    {
        // Test for random numbers
        long long lSeed = 1;
        Finance::Processes::BlackScholes sBS(0.08, 0.4, 1, lSeed);
        for (std::size_t i = 0 ; i < 10 ; ++i)
        {
            double sResult = sBS.Generate1(0.0, 1.0, 0.1);
            std::cout << "Step " << i << " : " << std::endl;
            std::cout << "Result : " << sResult << std::endl;
            
            std::cout << " " << std::endl;
        }
    }
    else if (iTest == 20)
    {
        // File writer
        FileWriter sWriter(std::vector<std::string>(10, "10"));
        sWriter.Write();
    }
    else if (iTest == 21)
    {
        // Map
        std::map<size_t, double> ConvertIntToDouble;
        ConvertIntToDouble.at(0) = 0.0;
        ConvertIntToDouble.at(1) = 1.0;
        ConvertIntToDouble.at(2) = 2.0;
        
        std::cout << ConvertIntToDouble.size() << std::endl;
    }
    else if (iTest == 22)
    {
        // Golf
        try
        {
            Golf::OfficialWorldGolfRankings sOGWR;
            
            Utilities::Interp::LinearInterpolator sOWGRDiscountCurve = sOGWR.GetDiscountCurve(Golf::OWGR), sTennisDiscountCurve = sOGWR.GetDiscountCurve(Golf::TENNIS);
            
            for (double dT = -2.5 ; dT < 1.0 ; dT += 0.041)
            {
                std::cout << dT << ";" << sOWGRDiscountCurve(dT) << ";" << sTennisDiscountCurve(dT) << std::endl;
            }
            
        }
        catch (Utilities::MyException & sException)
        {
            std::cout << "MyException caught : " << sException.what() << std::endl;
        }
        catch (std::exception & sException)
        {
            std::cout << "std::exception caught " << sException.what() << std::endl;
        }
        catch (...)
        {
            std::cout << "Unknown exception caught" << std::endl;
        }
    }
    else if (iTest == 23)
    {
        try
        {
            Golf::Tournament sTourChampionship2013("/Users/alexhum49/Documents/Workspace/CVA/CVATools/Input/Golf/Tournaments/TourChampionship2013.csv");
            
            sTourChampionship2013.Print();
        }
        catch(Utilities::MyException & sException)
        {
            std::cout << "MyException caught : " << sException.what() << std::endl;
        }
        catch (std::exception & sException)
        {
            std::cout << "std::exception caught " << sException.what() << std::endl;
        }
        catch(...)
        {
            std::cout << "Unknown exception caught" << std::endl;
        }
    }
    else if (iTest == 24)
    {
        try
        {
            Golf::Player sTigerWoods("/Users/alexhum49/Documents/Workspace/CVA/CVATools/Input/Golf/Players/Tiger_Woods.csv");
            sTigerWoods.Print();
        }
        catch(Utilities::MyException & sException)
        {
            std::cout << "MyException caught : " << sException.what() << std::endl;
        }
        catch (std::exception & sException)
        {
            std::cout << "std::exception caught " << sException.what() << std::endl;
        }
        catch(...)
        {
            std::cout << "Unknown exception caught" << std::endl;
        }
    }
    else if (iTest == 25)
    {
        DIR *dir;
        struct dirent *ent;
        std::string cDirectory = "/Users/alexhum49/Documents/Workspace/CVA/CVATools/Input/Golf/Players";
        if ((dir = opendir (cDirectory.c_str())) != NULL)
        {
            /* print all the files and directories within directory */
            while ((ent = readdir (dir)) != NULL)
            {
                std::string str = ent->d_name;
                unsigned long found = str.find_last_of(".");
                std::string cLastChar = str.substr(found+1, str.size());
                if (cLastChar == "csv" || cLastChar == "CSV")
                {
                    printf ("%s\n", ent->d_name);
                }
            }
            closedir (dir);
        }
        else
        {
            /* could not open directory */
            perror ("");
            return EXIT_FAILURE;
        }
    }
    else if (iTest == 26)
    {
        Golf::PlayerDataBase sDataBase ("/Users/alexhum49/Documents/Workspace/CVA/CVATools/Input/Golf/Players", Golf::TENNIS);
        
        std::cout << std::endl;
        
        sDataBase.ComputeRanking();
        
        for (std::size_t i = 0 ; i < sDataBase.GetDataBase().size() ; ++i)
        {
            sDataBase.GetDataBase()[i].PrintName();
        }
    }
    else if (iTest == 27)
    {
        //  HTTP Fetcher
        /*HttpFetcher sHTTP;
        sHTTP.simpleGetRequest("http://stackoverflow.com/questions/7168933/get-page-contents-in-c");*/
    }
    else if (iTest == 28)
    {
        int n = 3, nrot ;
        Utilities::Matrix<double> a (n,n), eigenvectors(4,4);
        Utilities::MyVector<double> dEigenValues(0.0, n);
        a(0,0) = a(n-1,0) = a(0,n-1) = a(n-1,n-1) = 2;
        for (int i = 1 ; i < n - 1 ; ++i)
        {
            a(0,i) = a(i,0) = a(i,n-1) = a(n-1, i) = 1;
        }
        
        Utilities::Eigendecomposition_jacobi(a, eigenvectors, dEigenValues, &nrot);
        
        for (int i = 0 ; i < n ; ++i)
        {
            std::cout << dEigenValues.at(i) << std::endl;
        }
    }
    else if (iTest == 29)
    {
        alglib::sparsematrix sparsematrix;
    }
    else if (iTest == 30)
    {
        //  Old require exception
        try
        {
            int i = 0 ;
            Utilities::requireException(i == 1, "i is not equal to 1", "main");
        }
        catch (Utilities::MyException & excep)
        {
            std::cout << "Old MyException caught : " << excep.what() << std::endl;
        }
        //  New require exception
        try
        {
            int i = 0 ;
            REQUIREEXCEPTION(i==1, "i is not equal to 1");
        }
        catch (Utilities::MyException & excep)
        {
            std::cout << "New MyException caught : " << excep.what() << std::endl;
        }
    }
    else if (iTest == 31)
    {
        std::vector<double> dStrikes(3,0.0), dVols(3, 0.0);
        dStrikes.at(0) = 0.75;
        dStrikes.at(1) = 1;
        dStrikes.at(2) = 1.25;
        
        dVols.at(0) = 0.25;
        dVols.at(1) = 0.20;
        dVols.at(2) = 0.23;
        Utilities::Interp::HermiteSplineCubicInterpolator Interp(dStrikes, dVols);
        
        for (double dStrike = 0.5 ; dStrike < 1.5 ; dStrike += 0.05)
            std::cout << dStrike << ";" << Interp(dStrike) << std::endl;
    }
    return 0;
}

int main()
{
    try
    {
        _main();
    }
    catch (Utilities::MyException & excep)
    {
        std::cout << "MyException caught : " << excep.what() << std::endl;
    }
    catch (std::exception & excep)
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