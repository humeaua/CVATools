//
//  RegressionTests.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 26/05/13.
//
//

#include "RegressionTests.h"
#include <vector>
#include <cmath>
#include "BondPricer.h"

void RegressionTest_BondPricing()
{
    //////////////////////////////////////////////////////////////
    //                                                          //
    //          Regression test for Bond Pricing                //
    //                                                          //
    //////////////////////////////////////////////////////////////
    try
    {
        std::cout << "Regression Test for Bond Pricing" << std::endl;
        
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
        
        Utilities::Date::MyDate sStart(11,05,2014), sEnd(11,05,2034), sToday(10, 5, 2013);
        Finance::YieldCurve sYieldCurve(sToday, "USD", "USD_YC_10_05_2013", dYC, Utilities::Interp::LIN);
        
        Finance::MyBasis eBasis = Finance::BONDBASIS;
        Finance::MyFrequency eFrequency = Finance::MyFrequencyAnnual;
        double dNotional = 1.;
        
        std::vector<double> dCoupons(20, 0.01);
        bool bIsFixedRate = true;
        
        Pricers::BondPricer sBondPricer(sToday, sStart, sEnd, sYieldCurve, eBasis, eFrequency, dCoupons, dNotional, bIsFixedRate);
        double dBondPrice = sBondPricer.Price();
        double dRefBondPrice = 0.720238, dRefYield = 0.027131, dRefISpread = -0.000262296, dRefZSpread = 0.000538938;
        double dError = 1.0e-5;
        
        std::size_t iError = 0;
        
        std::cout << "Test Bond Price : ";
        if (fabs(dBondPrice - dRefBondPrice) < dError)
        {
            std::cout << "SUCCEEDED" << std::endl;
        }
        else
        {
            std::cout << "FAILED" << std::endl;
            iError++;
        }
        
        std::cout << "Test Bond Yield : ";
        double dPriceToYield = sBondPricer.PriceToYield(dBondPrice);
        if (fabs(dPriceToYield - dRefYield) < dError)
        {
            std::cout << "SUCCEEDED" << std::endl;
        }
        else
        {
            std::cout << "FAILED" << std::endl;
            iError++;
        }
        
        std::cout << "Test Bond I-Spread : ";
        double dISpread = sBondPricer.I_Spread(dBondPrice);
        if (fabs(dISpread - dRefISpread) < dError)
        {
            std::cout << "SUCCEEDED" << std::endl;
        }
        else
        {
            std::cout << "FAILED" << std::endl;
            iError++;
        }
        
        std::cout << "Test Bond I-Spread : ";
        double dZSpread = sBondPricer.Z_Spread(dBondPrice);
        if (fabs(dZSpread - dRefZSpread) < dError)
        {
            std::cout << "SUCCEEDED" << std::endl;
        }
        else
        {
            std::cout << "FAILED" << std::endl;
            iError++;
        }
        
        if (iError > 0)
        {
            std::cout << "You must either correct the code or update the regresssion test" << std::endl;
        }
    }
    catch( std::exception & e)
    {
        std::cout << "Exception caught : " << e.what() << std::endl;
    }
    catch(...)
    {
        std::cout << "Unknown exception caught" << std::endl;
    }
}
