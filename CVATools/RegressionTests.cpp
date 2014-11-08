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
#include "Statistics.h"
#include "PayoffLinearization.h"
#include "PayoffVanillaOption.h"
#include "BlackScholes.h"
#include "VectorUtilities.h"
#include "InterExtrapolation.h"
#include <iomanip>

#include "SquareRoot.h"
#include "OrnsteinUhlenbeck.h"
#include "BlackScholes.h"
#include "StochCorrel.h"
#include "CEV.h"

#include "VolSmile.h"
#include "SVIParameterSolver.h"

#include "Analytic.h"
#include "NewtonSolver.h"
#include "BisectionSolver.h"
#include "Ticker.h"
#include "Sobol.h"
#include "MathFunctions.h"

//  Declaration of all the regression tests

bool RegressionTest::BondPricing(std::ostream & os) const
{
    //////////////////////////////////////////////////////////////
    //                                                          //
    //          Regression test for Bond Pricing                //
    //                                                          //
    //////////////////////////////////////////////////////////////
    try
    {
        //os << "Regression Test for Bond Pricing" << std::endl;
        
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
        
        const Utilities::Date::MyDate sStart(11,05,2014), sEnd(11,05,2034), sToday(10, 5, 2013);
        const Finance::Base::YieldCurve sYieldCurve(sToday, "USD", "USD_YC_10_05_2013", Utilities::GetPairOfVectorFromVectorOfPair(dYC));
        
        const Finance::Base::MyBasis eBasis = Finance::Base::BONDBASIS;
        const Finance::Base::MyFrequency eFrequency = Finance::Base::MyFrequencyAnnual;
        const double dNotional = 1.;
        
        const std::vector<double> dCoupons(20, 0.01);
        const bool bIsFixedRate = true;
         
        const Finance::Pricers::BondPricer sBondPricer(sStart, sEnd, sYieldCurve, eBasis, eFrequency, dCoupons, dNotional, bIsFixedRate);
        const double dBondPrice = sBondPricer.Price();
        const double dRefBondPrice = 0.717563489599423;
        const double dTolerance = 1.0e-10;
        
        os << "Test Bond Price : ";

        if (fabs(dBondPrice - dRefBondPrice) < dTolerance)
        {
            os << "SUCCEEDED" << std::endl;
        }
        else
        {
            os << "FAILED" << std::endl;
            return false;
        }
        
        os << "Test Bond Yield : ";
        const double dPriceToYield = sBondPricer.PriceToYield(dBondPrice);
        const double dRefYield = 0.0272162086597243;
        if (fabs(dPriceToYield - dRefYield) < dTolerance)
        {
            os << "SUCCEEDED" << std::endl;
        }
        else
        {
            os << "FAILED" << std::endl;
            return false;
        }
        
        os << "Test Bond I-Spread : ";
        const double dISpread = sBondPricer.I_Spread(dBondPrice);
        const double dRefISpread =-0.000364158958578442;
        if (fabs(dISpread - dRefISpread) < dTolerance)
        {
            os << "SUCCEEDED" << std::endl;
        }
        else
        {
            os << "FAILED" << std::endl;
            return false;
        }
        
        os << "Test Bond Z-Spread : ";
        const double dZSpread = sBondPricer.Z_Spread(dBondPrice);	
        const double dRefZSpread = 0.000384933028693842;
        if (fabs(dZSpread - dRefZSpread) < dTolerance)
        {
            os << "SUCCEEDED" << std::endl;
        }
        else
        {
            os << "FAILED" << std::endl;
            return false;
        }
    }
    catch(const Utilities::MyException & e)
    {
        os << "MyException caught : " << std::endl;
        os << e.what() << std::endl;
        return false;
    }
    catch(const std::exception & e)
    {
        os << "Exception caught : " << std::endl;
        os << e.what() << std::endl;
        return false;
    }
    catch(...)
    {
        os << "Unknown exception caught" << std::endl;
        return false;
    }
    return true;
}

bool RegressionTest::TimeStatistics(std::ostream & os) const
{
    try
    {
        // Regression Test Statistics Time
        std::size_t iNTimes = 10;
        os << std::endl;
        std::vector<double> dData(1000000, 1.0);
        double dTimeOld = 0.0, dTimeNew = 0.0;
        for (size_t iTimes = 0; iTimes < iNTimes ; ++iTimes)
        {
            clock_t tic = clock();
            double dResult = Maths::Statistics::MeanOld(dData);
            if (dResult != 1.0)
            {
                throw EXCEPTION("Mean Result is not 1.0");
            }
            dTimeOld += static_cast<double>(clock() - tic)/CLOCKS_PER_SEC;
            
            tic = clock();
            dResult = Maths::Statistics::Mean(dData);
            if (dResult != 1.0)
            {
                throw EXCEPTION("Mean Result is not 1.0");
            }
            dTimeNew += static_cast<double>(clock() - tic)/CLOCKS_PER_SEC;
        }
        os << "Mean old time elapsed  " << dTimeOld / iNTimes << " seconds" << std::endl;
        os << "Mean time elapsed  " << dTimeNew / iNTimes << " seconds" << std::endl;
        
        os << "Time ratio : " << dTimeNew / dTimeOld << std::endl;
        os << "Computation mean : ";
        if (dTimeNew < 1.25 * dTimeOld)
        {
            os << "SUCCEEDED" << std::endl;
        }
        else
        {
            os << "FAILED" << std::endl;
            return false;
        }
        
        std::cout << std::endl;
        dTimeNew = dTimeOld = 0.0;
        for (size_t iTimes = 0; iTimes < iNTimes ; ++iTimes)
        {
            clock_t tic = clock();
            double dResult = Maths::Statistics::VarianceOld(dData);
            if (dResult != 0.0)
            {
                throw EXCEPTION("Variance is not 0.0");
            }
            dTimeOld += static_cast<double>(clock() - tic)/CLOCKS_PER_SEC;
            
            tic = clock();
            dResult = Maths::Statistics::Variance(dData);
            if (dResult != 0.0)
            {
                throw EXCEPTION("Variance is not 0.0");
            }
            dTimeNew += static_cast<double>(clock() - tic)/CLOCKS_PER_SEC;
        }
        os << "Variance old time elapsed  " << dTimeOld / iNTimes << " seconds" << std::endl;
        os << "Variance time elapsed  " << dTimeNew / iNTimes << " seconds" << std::endl;
        
        os << "Time ratio : " << dTimeNew / dTimeOld << std::endl;
        os << "Computation variance : ";
        //  New algorithm seems to be around 3 times slower
        if (3.0 * dTimeNew > dTimeOld)
        {
            os << "SUCCEEDED" << std::endl;
        }
        else
        {
            os << "FAILED" << std::endl;
            return false;
        }
    }
    catch (const Utilities::MyException & excep)
    {
        os << "MyException caught : " << excep.what() << std::endl;
        return false;
    }
    catch (const std::exception & excep)
    {
        os << "std::exception caught : " << excep.what() << std::endl;
        return false;
    }
    catch (...)
    {
        os << "Unknown exception caught" << std::endl;
        return false;
    }
    return true;
}

bool RegressionTest::PayoffLinearization(std::ostream & os) const
{
    // Payoff Linearisation
    Finance::Payoff::PayoffVanillaOption sPayoff(1.0, ::Finance::Payoff::CALL);
    long long lSeed = 0;
    Finance::Processes::BlackScholes sBlackScholes(0.0, 0.4, 1.0, lSeed);
    
    Maths::PayoffLinearization sPayoffLinearization(1000);
    
    std::vector<double> dSimulationsDates;
    dSimulationsDates.push_back(0.0);
    dSimulationsDates.push_back(1.0);
    
    /*
     Cst : -0.485756
     Coef Stock : 0.648333
     */
    
    const double dRefConstant = -0.467719463611643, dRefCoefStock = 0.628602529249528;
    const std::pair<double, double> dRegCoefs = sPayoffLinearization.Linearise(sBlackScholes, sPayoff, dSimulationsDates);
    const double dEpsilon = 1e-6;
    os << "Payoff linearization : " ;
    if (fabs(dRegCoefs.first - dRefCoefStock) < dEpsilon && fabs(dRegCoefs.second - dRefConstant) < dEpsilon)
    {
        os << "SUCCEDEED" << std::endl;
    }
    else
    {
        os << "FAILED" << std::endl;
        return false;
    }
    
    return true;
}

bool RegressionTest::Interpolation(std::ostream & os) const
{
    double variables[] = {1.0, 2.0, 3.0, 3.5}, values[] = {1.0, 0.0, 1.0, 1.0};
    std::vector<double> vectvar(variables, variables + 4), vectvalues(values, values + 4);
    
    Utilities::Interp::LinearInterpolator lin(vectvar, vectvalues);
    Utilities::Interp::LogLinDFInterpolator loglindf(vectvar, vectvalues);
    Utilities::Interp::LeftContinuousInterpolator leftcontinuous(vectvar, vectvalues);
    Utilities::Interp::RightContinuousInterpolator rightcontinuous(vectvar, vectvalues);
    Utilities::Interp::HermiteSplineCubicInterpolator hermite(vectvar, vectvalues);
    Utilities::Interp::HermiteDegree5Interpolator hermite5(vectvar, vectvalues);
    double valuesreflin[] = {1,1,1,1,1,1,1,1,1,1,0.9,0.8,0.7,0.6,0.5,0.4,0.3,0.2,0.1,6.38378e-16,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1,1,1,1,1,1,1,1,1,1};
    double valuesrefloglindf[] = {19,9,5.66666667,4,3,2.33333333,1.85714286,1.5,1.22222222,1,0.818181818,0.666666667,0.5384615,0.428571429,0.333333333,0.25,0.176470588,0.111111111,0.0526315789,6.66133815e-16,0.142857143,0.272727273,0.391304348,0.5,0.6,0.692307692,0.777777778,0.857142857,0.931034483,1,1,1,1,1,1,1,1,1,1};
    double valuesrefleftcontinuous[] = {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    double valuesrefrightcontinuous[] ={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1};
    double valueshermite[] = {-1.349,-0.792,-0.323,0.064,0.375,0.616,0.793,0.912,0.979,1,0.981,0.928,0.847,0.744,0.625,0.496,0.363,0.232,0.109,4.4408921e-16,0.109,0.232,0.363,0.496,0.625,0.744,0.847,0.928,0.981,1,1,1,1,1,1,1,1,1,1};
    double valueshermite5[] = {12.39427,8.33184,5.48301,3.56608,2.34375,1.61952,1.23409,1.06176,1.00683,1,0.99477,0.96384,0.89551,0.79008,0.65625,0.50752,0.35859,0.22176,0.10333,4.4408921e-16,0.109,0.232,0.363,0.496,0.625,0.744,0.847,0.928,0.981,1,1,1,1,1,1,1,1,1,1};
    double dErrorlin = 0.0, dErrorloglindf = 0.0, dErrorleftcontinuous = 0.0, dErrorrightcontinuous = 0.0, dErrorhermite = 0.0, dErrorhermite5 = 0.0;
    for (int i = 0 ; i < 39 ;  i++)
    {
        double var = 0.1 * (i+1);
        dErrorlin               += std::abs(lin(var) - valuesreflin[i]);
        dErrorloglindf          += std::abs(loglindf(var) - valuesrefloglindf[i]);
        dErrorleftcontinuous    += std::abs(leftcontinuous(var) - valuesrefleftcontinuous[i]);
        dErrorrightcontinuous   += std::abs(rightcontinuous(var) - valuesrefrightcontinuous[i]);
        dErrorhermite           += std::abs(hermite(var) - valueshermite[i]);
        dErrorhermite5          += std::abs(hermite5(var) - valueshermite5[i]);
    }
    
    const double dTolerance = 1e-5;
    os << "Linear interpolation : ";
    if (dErrorlin < dTolerance)
    {
        os << "SUCCEEDED" << std::endl;
    }
    else
    {
        os << "FAILED" << std::endl;
        return false;
    }
    os << "Log-lin DF interpolation : ";
    if (dErrorloglindf < dTolerance)
    {
        os << "SUCCEEDED" << std::endl;
    }
    else
    {
        os << "FAILED" << std::endl;
        return false;
    }
    os << "Left continuous interpolation : ";
    if (dErrorleftcontinuous < dTolerance)
    {
        os << "SUCCEEDED" << std::endl;
    }
    else
    {
        os << "FAILED" << std::endl;
        return false;
    }
    os << "Right continuous interpolation : ";
    if (dErrorrightcontinuous < dTolerance)
    {
        os << "SUCCEEDED" << std::endl;
    }
    else
    {
        os << "FAILED" << std::endl;
        return false;
    }
    os << "Hermite spline cubic interpolation  : ";
    if (dErrorhermite < dTolerance)
    {
        os << "SUCCEEDED" << std::endl;
    }
    else
    {
        os << "FAILED" << std::endl;
        return false;
    }
    os << "Hermite degree 5 interpolation  : ";
    if (dErrorhermite5 < dTolerance)
    {
        os << "SUCCEEDED" << std::endl;
    }
    else
    {
        os << "FAILED" << std::endl;
        return false;
    }
    return true;
}

bool RegressionTest::VolatilitySurfaceInterpolation(std::ostream & os) const
{
    const double dFwdRef = 1.0, T = 1.0;
    const double strikes[] = {0.6, 0.75, 0.9, 1.0, 1.1, 1.25, 1.4}, vols[] = {0.20, 0.180, 0.150, 0.125, 0.164, 0.197, 0.223};
    const std::vector<double> strikesvect(strikes, strikes + 7), volsvect(vols, vols + 7);
    Finance::Volatility::VolSmile volSmile(strikesvect, volsvect, dFwdRef, T);
    Finance::Volatility::SVIParameterSolver sviParameterSolver(dFwdRef);
    
    try
    {
        sviParameterSolver.Solve(volSmile, true); // use parabola
    }
    catch (const Utilities::MyException & excep)
    {
        os << excep.what() << std::endl;
        return false;
    }
    catch (const std::exception & excep)
    {
        os << excep.what() << std::endl;
        return false;
    }
    catch (...)
    {
        os << "Unknown exception caught" << std::endl;
        return false;
    }
    
    os << "Non-Arbitrageability of smile : " << volSmile.IsArbitrageFree() << std::endl;
    os << "SVI Parametrisation arbitrable ? " << sviParameterSolver.IsArbitrable(T) << std::endl;

    
    double dVolHermiteInterp[] = {0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.199955909,0.199689734,0.199081336,0.198094904,0.196754089,0.19512155,0.193282206,0.191329615,0.189354987,0.187438405,0.185641902,0.184004098,0.182536136,0.181218712,0.18,0.177819828,0.175742583,0.173828076,0.172080715,0.170466648,0.168928276,0.167396491,0.165800937,0.164078559,0.162180664,0.160078705,0.15776894,0.155276176,0.152656598,0.15,0.14717476,0.14340999,0.138521685,0.132949327,0.127473701,0.122974304,0.120221805,0.119701462,0.121463895,0.125,0.129374691,0.134125924,0.138991353,0.143745486,0.148209001,0.152256557,0.15582327,0.158909988,0.161587532,0.164,0.166327361,0.168636065,0.170945902,0.173265008,0.175592626,0.177921568,0.180240405,0.1825354,0.18479223,0.186997494,0.189140045,0.191212151,0.193210507,0.195137106,0.197,0.198859901,0.200861613,0.203076471,0.205502719,0.208085317,0.210733763,0.21333809,0.215783199,0.217961653,0.21978509,0.221194336,0.222168368,0.222732195,0.22296377,0.223,0.223,0.223,0.223,0.223,0.223,0.223,0.223,0.223,0.223};
    double dSVIParametrisationParabola[] = {0.178893591,0.178650672,0.178418266,0.178196216,0.177984381,0.177782629,0.177590842,0.177408913,0.177236745,0.177074248,0.176921343,0.176777956,0.176644019,0.17651947,0.176404253,0.176298313,0.176201599,0.176114063,0.176035659,0.175966338,0.175906055,0.175854763,0.175812412,0.175778951,0.175754327,0.175738481,0.175731354,0.175732879,0.175742984,0.175761595,0.175788628,0.175823995,0.1758676,0.175919343,0.175979115,0.176046799,0.176122273,0.176205408,0.176296066,0.176394105,0.176499373,0.176611716,0.176730971,0.176856971,0.176989542,0.177128507,0.177273684,0.177424889,0.177581933,0.177744625,0.177912772,0.178086179,0.178264652,0.178447995,0.178636012,0.178828508,0.179025291,0.179226167,0.179430946,0.179639442,0.179851468,0.180066845,0.180285392,0.180506937,0.180731308,0.180958338,0.181187865,0.181419733,0.181653787,0.181889878,0.182127864,0.182367605,0.182608967,0.182851819,0.183096038,0.183341502,0.183588097,0.183835712,0.184084239,0.184333577,0.184583629,0.184834299,0.185085501,0.185337147,0.185589156,0.185841451,0.186093958,0.186346606,0.186599327,0.186852059,0.187104741,0.187357314,0.187609725,0.187861922,0.188113855,0.188365479,0.188616748,0.188867623,0.189118063,0.189368031};
    double dSmileConvexity[] = {0,0,0,0,0,0,0,0,0,0,1.29359771e-14,0.949704883,1.78164114,2.4290384,2.87421491,3.13579809,3.25859461,3.30559555,3.3517018,3.47883388,3.77215495,4.31718721,5.19764375,6.49383184,8.28151098,0.0355555556,0.644330861,1.15435063,1.54363225,1.81171569,1.97483844,2.06194588,2.11140265,2.16829215,2.28220896,2.50546423,2.89163665,3.49441237,4.36666589,5.55974179,0.037037037,0.360276838,0.649070063,0.829186723,0.884705044,0.846918233,0.784871718,0.797308011,1.00582657,1.54909201,0.025,0.471160929,0.788641532,0.943061447,0.952618404,0.878606525,0.817218999,0.892474478,1.25012642,2.05243197,-0.032231405,0.303823668,0.583122853,0.788223906,0.914127454,0.966309165,0.958991995,0.91363123,0.857588159,0.822970886,0.845623226,0.964244777,1.21962711,1.65399272,2.31042493,-0.01664,0.29481522,0.553271223,0.745602239,0.868917411,0.929103772,0.939527779,0.919879376,0.895144167,0.894690707,0.95146125,1.10125542,1.38209733,1.83367767,2.49686297,0,0,0,0,0,0,0,0,0,0};
    double dSmileSkew[] = {0,0,0,0,0,0,0,0,0,0,-5.94104744e-31,-0.00282663416,-0.00948806359,-0.0177879306,-0.0261397432,-0.0334598681,-0.0390773866,-0.0426581729,-0.0441409854,-0.0436837089,-0.0416181832,-0.0384123008,-0.0346382569,-0.0309460151,-0.0280411887,-0.04,-0.0390942586,-0.0364754161,-0.0333275637,-0.0304959997,-0.0285385681,-0.027770216,-0.0283016515,-0.0300728658,-0.0328821817,-0.0364114042,-0.0402475734,-0.0439017534,-0.0468252377,-0.0484234993,-0.0277777778,-0.0336819672,-0.0459154924,-0.0562702285,-0.0597375166,-0.0540647001,-0.0393628374,-0.0177598572,0.00690592272,0.0293564136,0.039,0.0439307097,0.046218974,0.046166346,0.0441710164,0.040712531,0.0363382327,0.0316512487,0.0272998572,0.0239680904,0.03,0.0295757139,0.0294916847,0.0295799156,0.0297097648,0.0297839037,0.0297346528,0.0295206602,0.0291238913,0.0285469022,0.0278103697,0.0269508553,0.0260187821,0.0250766045,0.024197154,0.0208,0.0216657732,0.0238350792,0.0263592577,0.0285261241,0.0298364062,0.0299821628,0.0288270217,0.0263880872,0.0228193809,0.0183966904,0.0135037119,0.0086193804,0.00430629163,0.00120012695,0,0,0,0,0,0,0,0,0,0};
    double dErrorInterpHermite = 0.0, dErrorSVIParabola = 0.0, dErrorSmileConvexity = 0.0, dErrorSmileSkew = 0.0;
    int i = 0;
    for (double dStrike = 0.50 ; dStrike < 1.5 ; dStrike += 0.01, ++i)
    {
        dErrorInterpHermite += std::abs(dVolHermiteInterp[i] - volSmile(dStrike));
        dErrorSVIParabola += std::abs(sviParameterSolver(dStrike) - dSVIParametrisationParabola[i]);
        dErrorSmileConvexity += std::abs(volSmile.volatilityConvexity(dStrike) - dSmileConvexity[i]);
        dErrorSmileSkew += std::abs(volSmile.skew(dStrike) - dSmileSkew[i]);
    }
    const double dTolerance = 1e-06;
    os << "Hermite Interpolation of smile : ";
    if (dErrorInterpHermite < dTolerance)
    {
        os << "SUCCEEDED" << std::endl;
    }
    else
    {
        os << "FAILED" << std::endl;
        return false;
    }
    os << "SVI Parametrisation of smile : " ;
    if (dErrorSVIParabola < dTolerance)
    {
        os << "SUCCEEDED" << std::endl;
    }
    else
    {
        os << "FAILED. Error = " << dErrorSVIParabola << std::endl;
        return false;
    }
    os << "Smile skew : " ;
    if (dErrorSmileSkew < dTolerance)
    {
        os << "SUCCEEDED" << std::endl;
    }
    else
    {
        os << "FAILED" << std::endl;
        return false;
    }
    os << "Convexity of smile : " ;
    if (dErrorSmileConvexity < dTolerance)
    {
        os << "SUCCEEDED" << std::endl;
    }
    else
    {
        os << "FAILED" << std::endl;
        return false;
    }
    return true;
}

bool RegressionTest::ProcessPathSimulation(std::ostream & os) const
{
    const double dX0 = 1.0;
    
    long long lSeed = 0;
    const Finance::Processes::SquareRoot squareRoot(0.1, 1.0, 0.1, dX0, lSeed);
    const Finance::Processes::OrnsteinUhlenbeck ornsteinUhlenbeck(0.1, 1.0, 0.1, dX0, lSeed);
    const Finance::Processes::BlackScholes blackScholes(0.02, 0.1, dX0, lSeed);
    const Finance::Processes::StochCorrel stochCorrel(1.0, 0, 0.4, dX0 - 1.0, lSeed);
    const Finance::Processes::CEV cev(0.5, 1.0, lSeed);
    const double dDates[] = {0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0};
    std::vector<double> DatesVec(dDates, dDates + 21);
    const double dTolerance = 1e-6;
    
    std::vector<double> ResultsSR = squareRoot.simulate1path(DatesVec),
                        ResultsOU = ornsteinUhlenbeck.simulate1path(DatesVec),
                        ResultsBS = blackScholes.simulate1path(DatesVec),
                        ResultsSC = stochCorrel.simulate1path(DatesVec),
                        ResultsCEV = cev.simulate1path(DatesVec);
    
    const double dRefValuesSquareRoot[] = {1,1.01533189,1.00218429,0.980863849,0.951722112,0.926746364,0.915307718,0.945391067,0.887362489,0.896643275,0.940587215,0.940422193,0.961310737,0.920984543,0.977360754,0.961919216,0.984237052,0.98193395,1.04122305,1.0258744,1.02188529};
    const double dRefValuesOU[] = {1,0.999208646,1.01024586,1.04327062,1.0151356,1.03420104,1.02086556,1.04054557,1.05788609,1.06227928,1.01526912,0.952106248,0.976487794,1.01307013,1.02616416,1.0676393,1.07698467,1.08466054,1.16087981,1.16508758,1.11629776};
    const double dRefValuesBS[] = {1,1.00070493,1.01337791,1.04925637,1.0219766,1.04346905,1.0314758,1.05387909,1.0744517,1.08145192,1.03373856,0.971762002,0.996885123,1.03552707,1.0509566,1.09762101,1.11039261,1.12153443,1.21366543,1.22260359,1.16777423};
    const double dRefValuesSC[] = {0,-0.00318125765,0.0414593747,0.170569407,0.0445972641,0.1175252,0.0544624305,0.12910955,0.187557141,0.189330344,-0.0118042998,-0.263968357,-0.146158452,0.0123023101,0.0642886051,0.225600951,0.243368035,0.253124662,0.528737107,0.498240656,0.286494823};
    const double dRefValuesCEV[] = {1,0.943694164,1.00254485,1.33077638,0.903054546,1.03706766,0.862037294,0.994031805,1.12987488,1.12602925,0.648990246,0.377213853,0.429020783,0.533429262,0.572333617,0.763891414,0.802900615,0.832229009,1.61812175,1.60739942,0.813433722};
    double dDiffSquareRoot = 0.0, dDiffOU = 0.0, dDiffBS = 0.0, dDiffSC = 0.0, dDiffCEV = 0.0;
    for (std::size_t iDate = 0 ; iDate < DatesVec.size() ; ++iDate)
    {
        //os << std::setprecision(9) << ResultsCEV[iDate] << std::endl;
        dDiffSquareRoot += std::abs(dRefValuesSquareRoot[iDate] - ResultsSR[iDate]);
        dDiffOU += std::abs(dRefValuesOU[iDate] - ResultsOU[iDate]);
        dDiffBS += std::abs(dRefValuesBS[iDate] - ResultsBS[iDate]);
        dDiffSC += std::abs(dRefValuesSC[iDate] - ResultsSC[iDate]);
        dDiffCEV += std::abs(dRefValuesCEV[iDate] - ResultsCEV[iDate]);
    }
    
    os << "Square Root process Simulation : ";
    if (dDiffSquareRoot < dTolerance)
    {
        os << "SUCCEEDED" << std::endl;
    }
    else
    {
        os << "FAILED" << std::endl;
        return false;
    }
    os << "Ornstein Ulhenbeck process Simulation : ";
    if (dDiffOU < dTolerance)
    {
        os << "SUCCEEDED" << std::endl;
    }
    else
    {
        os << "FAILED" << std::endl;
        return false;
    }
    os << "Black Scholes process Simulation : ";
    if (dDiffBS < dTolerance)
    {
        os << "SUCCEEDED" << std::endl;
    }
    else
    {
        os << "FAILED" << std::endl;
        return false;
    }
    os << "Stochastic correlation process Simulation : ";
    if (dDiffSC < dTolerance)
    {
        os << "SUCCEEDED" << std::endl;
    }
    else
    {
        os << "FAILED" << std::endl;
        return false;
    }
    os << "CEV process Simulation : ";
    if (dDiffCEV < dTolerance)
    {
        os << "SUCCEEDED" << std::endl;
    }
    else
    {
        os << "FAILED" << std::endl;
        return false;
    }
    return true;
}

//  Regression test for date
bool RegressionTest::Date(std::ostream & os) const
{
    Utilities::Date::MyDate sToday(3,2,2014);
    
    os << "Today is " << sToday.Print() << std::endl;
    sToday = sToday.Add(1, Utilities::Date::DAY);
    sToday = sToday.Add(1, Utilities::Date::WEEK);
    sToday = sToday.Add(1, Utilities::Date::MONTH);
    sToday = sToday.Add(1, Utilities::Date::YEAR);
    sToday = sToday.Add(1, Utilities::Date::BUSINESSDAY);
    Utilities::Date::MyDate finalDate(12, 3, 2015);
    if (sToday == finalDate)
    {
        os << "SUCCEEDED" << std::endl;
    }
    else
    {
        os << "FAILED" << std::endl;
        return false;
    }
    return true;
}

bool RegressionTest::AnalyticFormulae(std::ostream & os) const
{
    const double dFwdRef = 1.0, T = 1.0, spot = 1.0;
    const double strikes[] = {0.6, 0.75, 0.9, 1.0, 1.1, 1.25, 1.4}, vols[] = {0.20, 0.180, 0.150, 0.125, 0.164, 0.197, 0.223};
    const double observationTimes[] = {0.0, 0.5, 1.0};
    const std::vector<double> strikesvect(strikes, strikes + 7), volsvect(vols, vols + 7), observationTimesvect(observationTimes, observationTimes + 3);
    std::vector<std::pair<double, double> > pastFixings;
    pastFixings.push_back(std::make_pair(-1.0, 0.9));
    pastFixings.push_back(std::make_pair(-0.5, 1.1));
    Finance::Volatility::VolSmile volSmile(strikesvect, volsvect, dFwdRef, T);
    
    Finance::Pricers::Analytic sAnalytic;
    
    const double volatility = 0.150, rate = 0.02;
    
    const double
    ATMFCallRef = 0.0586014601,
    ATMFPutRef = 0.0586014601,
    Call110Ref = 0.0245073664,
    PUT110Ref = 0.122527234,
    DigitalnoSmileATMFRef = 0.460798607,
    DigitalSmileATMFRef =0.450454163,
    VegaATMFRef = 0.389944432,
    Digital90NoSmileRef = 0.720252526,
    Digital90SmileRef = 0.728282006,
    AsianOptionRef = 0.0343143823;

    double error = 0.0;
    error += std::abs(sAnalytic.VanillaPrice(dFwdRef, dFwdRef, volatility, T, rate, Finance::Payoff::CALL) - ATMFCallRef);
    error += std::abs(sAnalytic.VanillaPrice(dFwdRef, dFwdRef, volatility, T, rate, Finance::Payoff::PUT) - ATMFPutRef);
    error += std::abs(sAnalytic.VanillaPrice(dFwdRef, 1.1 * dFwdRef, volatility, T, rate, Finance::Payoff::CALL) - Call110Ref);
    error += std::abs(sAnalytic.VanillaPrice(dFwdRef, 1.1 * dFwdRef, volatility, T, rate, Finance::Payoff::PUT) - PUT110Ref);
    error += std::abs(sAnalytic.DigitalPrice(dFwdRef, dFwdRef, volatility, T, rate, Finance::Payoff::CALL) - DigitalnoSmileATMFRef);
    error += std::abs(sAnalytic.DigitalPrice(dFwdRef, dFwdRef, volSmile, T, rate, Finance::Payoff::CALL) - DigitalSmileATMFRef);
    error += std::abs(sAnalytic.VegaVanillaOption(dFwdRef, dFwdRef, volatility, T, rate, Finance::Payoff::CALL) - VegaATMFRef);
    error += std::abs(sAnalytic.VegaVanillaOption(dFwdRef, dFwdRef, volatility, T, rate, Finance::Payoff::PUT) - VegaATMFRef);
    error += std::abs(sAnalytic.DigitalPrice(dFwdRef, 0.9 *dFwdRef, volatility, T, rate, Finance::Payoff::CALL) - Digital90NoSmileRef);
    error += std::abs(sAnalytic.DigitalPrice(dFwdRef, 0.9 * dFwdRef, volSmile, T, rate, Finance::Payoff::CALL) - Digital90SmileRef);
    error += std::abs(sAnalytic.AsianOption(spot, dFwdRef, Finance::Payoff::CALL, volatility, T, rate, observationTimesvect, pastFixings) - AsianOptionRef);
    
    bool bOutput = false;
    if (bOutput)
    {
        os << std::setprecision(9);
        os << "ATMFCallRef = " << sAnalytic.VanillaPrice(dFwdRef, dFwdRef, volatility, T, rate, Finance::Payoff::CALL) << ",";
        os << " ATMFPutRef = " << sAnalytic.VanillaPrice(dFwdRef, dFwdRef, volatility, T, rate, Finance::Payoff::PUT) << ",";
        os << " Call110Ref = " << sAnalytic.VanillaPrice(dFwdRef, 1.1 * dFwdRef, volatility, T, rate, Finance::Payoff::CALL) << ",";
        os << " PUT110Ref = " << sAnalytic.VanillaPrice(dFwdRef, 1.1 * dFwdRef, volatility, T, rate, Finance::Payoff::PUT) << ",";
        os << " DigitalnoSmileATMFRef = " << sAnalytic.DigitalPrice(dFwdRef, dFwdRef, volatility, T, rate, Finance::Payoff::CALL) << ",";
        os << " DigitalSmileATMFRef =" << sAnalytic.DigitalPrice(dFwdRef, dFwdRef, volSmile, T, rate, Finance::Payoff::CALL) << ",";
        os << " VegaATMFRef = " << sAnalytic.VegaVanillaOption(dFwdRef, dFwdRef, volatility, T, rate, Finance::Payoff::CALL) << ",";
        os << " Digital90NoSmileRef = " << sAnalytic.DigitalPrice(dFwdRef, 0.9 *dFwdRef, volatility, T, rate, Finance::Payoff::CALL) << ",";
        os << " Digital90SmileRef = " << sAnalytic.DigitalPrice(dFwdRef, 0.9 * dFwdRef, volSmile, T, rate, Finance::Payoff::CALL) ;
        os << " Asian option = " << sAnalytic.AsianOption(spot, dFwdRef, Finance::Payoff::CALL, volatility, T, rate, observationTimesvect, pastFixings) << std::endl;
        os << ";" << std::endl;
    }
    
    const double tolerance = 1e-06;
   
    if (error < tolerance)
    {
        os << "SUCCEEDED" << std::endl;
    }
    else
    {
        os << "FAILED" << std::endl;
        return false;
    }
    return true;
}


bool RegressionTest::MatrixInversion(std::ostream &os) const
{
    Utilities::Matrix<double> matrix(3,3), inverse(3,3), refinvmatrix(3,3);
    matrix(0,0) = matrix(0,1) = matrix(0,2) = 1;
    matrix(1,0) = 3;
    matrix(1,1) = 4;
    matrix(1,2) = 5;
    matrix(2,0) = 6;
    matrix(2,1) = 12;
    matrix(2,2) = 20;
    
    refinvmatrix(0,0) = 10;
    refinvmatrix(0,1) = -4;
    refinvmatrix(0,2) = 0.5;
    refinvmatrix(1,0) = -15;
    refinvmatrix(1,1) = 7;
    refinvmatrix(1,2) = -1;
    refinvmatrix(2,0) = 6;
    refinvmatrix(2,1) = -3;
    refinvmatrix(2,2) = 0.5;
    
    Utilities::matrixinverse(inverse, matrix);
    
#ifdef DEBUG
    inverse.print(os);
    refinvmatrix.print(os);
#endif
    
    const double tolerance = 1e-8;
    double error = 0.0;
    for (size_t i = 0 ; i < 3 ; ++i)
    {
        for (size_t j = 0 ; j < 3 ; ++j)
        {
            error += std::abs(refinvmatrix[i][j] - inverse[i][j]);
        }
    }
    
    if (error < tolerance)
    {
        os << "SUCCEEDED" << std::endl;
    }
    else
    {
        os << "FAILED" << std::endl;
        return false;
    }
    return true;
}

namespace
{
    double MySqrt(double x);
    double MySqrt(double x)
    {
        return sqrt(x) - 1;
    }
    
    double MySqrtDeriv(double x);
    double MySqrtDeriv(double x)
    {
        return 0.5 / sqrt(x);
    }
}

bool RegressionTest::NewtonSolver(std::ostream &os) const
{
    Utilities::Solvers::NewtonParams params;
    params.m_dFirstGuess = 2.0;
    
    Utilities::Solvers::NewtonSolver<double(double)> solver(MySqrt, MySqrtDeriv, params);
    Utilities::Solvers::BisectionSolver<double(double)> solver2(MySqrt);
    
    double ref = 1.0;
    const double tolerance = params.m_dTolerance;
    const double calc = solver.Solve();
    if (std::abs(calc - ref) < tolerance)
    {
        os << "SUCCEEDED" << std::endl;
    }
    else
    {
        os << "FAILED";
        return false;
    }
    return true;
}

bool RegressionTest::Ticker(std::ostream &os) const
{
    Utilities::Ticker<double> tick("tickdouble");
    
    tick.Store(10.0);
    double res = tick.Instance();
    std::string name = tick.Name();
    const double tolerance = 1e-10;
    if (name == "tickdouble.1" && std::abs(res - 10.0) < tolerance)
    {
        os << "SUCCEEDED" << std::endl;
        return true;
    }
    else
    {
        os << "FAILED" << std::endl;
        return false;
    }
}

bool RegressionTest::Sobol(std::ostream &os) const
{
    const int dim_num = 1110;
    long long int seed = 110;
    std::vector<double> quasi1(dim_num, 0.0);
    i8_sobol (dim_num,&seed,Utilities::GetPointer(quasi1));
    
    const double refvalues[] = {0.6015625,0.3203125,0.8671875,0.5390625,0.1953125,0.9140625,0.8203125,0.0546875,0.9765625,0.3828125,0.0390625,0.0234375,0.2109375,0.4140625,0.3046875,0.2578125,0.2421875,0.7734375,0.9296875,0.8828125,0.6015625,0.6171875,0.7890625,0.4609375,0.7890625,0.1953125,0.8359375,0.7421875,0.4765625,0.7265625,0.4609375,0.1796875,0.1015625,0.8203125,0.3671875,0.0390625,0.1953125,0.4140625,0.3203125,0.0546875,0.7578125,0.3359375,0.7109375,0.4296875,0.8984375,0.5078125,0.7265625,0.8515625,0.3515625,0.4609375,0.9609375,0.7109375,0.8828125,0.9765625,0.7734375,0.9921875,0.6484375,0.6953125,0.2421875,0.6171875,0.4765625,0.3046875,0.7421875,0.6015625,0.0703125,0.8828125,0.8359375,0.1484375,0.7890625,0.3203125,0.4140625,0.6640625,0.5078125,0.9609375,0.7890625,0.2734375,0.5078125,0.2734375,0.9765625,0.6640625,0.6171875,0.1640625,0.4765625,0.3359375,0.2578125,0.1953125,0.1015625,0.7734375,0.4453125,0.4765625,0.1171875,0.1953125,0.5546875,0.4609375,0.8359375,0.3515625,0.9921875,0.0546875,0.6953125,0.4140625,0.2578125,0.1640625,0.4296875,0.8203125,0.1796875,0.5859375,0.4921875,0.6171875,0.1328125,0.7109375,0.1171875,0.9453125,0.4765625,0.8515625,0.7734375,0.3203125,0.3984375,0.0078125,0.8671875,0.3828125,0.8515625,0.9921875,0.3515625,0.8203125,0.3984375,0.7578125,0.7734375,0.1953125,0.4921875,0.2265625,0.0546875,0.0546875,0.0234375,0.7578125,0.7578125,0.4921875,0.0078125,0.5546875,0.3203125,0.4296875,0.1328125,0.6484375,0.4453125,0.3984375,0.8671875,0.4453125,0.3515625,0.9609375,0.8046875,0.0234375,0.8984375,0.3671875,0.0078125,0.6015625,0.3046875,0.3671875,0.9296875,0.9765625,0.1796875,0.7109375,0.6171875,0.7890625,0.7421875,0.4296875,0.5234375,0.1328125,0.2265625,0.4765625,0.7578125,0.6484375,0.5078125,0.6640625,0.2734375,0.2421875,0.4140625,0.7890625,0.4453125,0.1953125,0.3671875,0.4296875,0.3203125,0.5078125,0.8203125,0.1484375,0.6015625,0.2578125,0.0390625,0.0546875,0.9140625,0.7109375,0.0859375,0.0234375,0.6015625,0.4453125,0.4765625,0.7109375,0.1640625,0.8515625,0.1484375,0.0078125,0.1953125,0.7265625,0.9609375,0.7265625,0.4921875,0.2734375,0.3984375,0.5546875,0.1796875,0.1953125,0.0234375,0.5859375,0.2421875,0.8359375,0.2890625,0.3671875,0.0234375,0.1328125,0.5546875,0.5703125,0.8203125,0.0390625,0.1328125,0.2265625,0.3515625,0.1796875,0.6171875,0.0546875,0.4296875,0.6953125,0.1640625,0.6640625,0.7578125,0.6796875,0.1015625,0.3671875,0.6328125,0.4609375,0.0859375,0.9765625,0.5703125,0.5234375,0.5390625,0.5859375,0.0390625,0.6796875,0.7734375,0.1328125,0.3515625,0.9140625,0.9296875,0.6796875,0.5859375,0.0859375,0.2890625,0.7109375,0.1953125,0.0078125,0.1953125,0.8203125,0.4140625,0.0390625,0.7890625,0.2890625,0.8828125,0.8671875,0.1953125,0.3203125,0.4921875,0.1640625,0.3046875,0.8046875,0.3046875,0.3515625,0.4296875,0.7421875,0.1015625,0.5703125,0.7109375,0.6796875,0.9296875,0.6484375,0.7109375,0.3671875,0.2265625,0.3515625,0.6015625,0.6328125,0.1328125,0.8671875,0.3984375,0.6640625,0.4921875,0.2421875,0.2265625,0.6953125,0.2890625,0.1953125,0.5859375,0.8515625,0.4140625,0.6796875,0.1015625,0.0859375,0.9921875,0.8671875,0.0703125,0.6484375,0.8828125,0.3359375,0.7578125,0.9765625,0.0859375,0.6015625,0.7734375,0.1953125,0.7265625,0.4453125,0.4765625,0.1484375,0.2421875,0.1015625,0.3515625,0.2421875,0.6640625,0.1328125,0.2421875,0.5546875,0.0546875,0.6953125,0.9609375,0.4609375,0.2265625,0.7734375,0.6640625,0.0390625,0.3828125,0.1796875,0.2109375,0.5859375,0.7734375,0.4921875,0.4296875,0.4296875,0.9609375,0.7578125,0.5234375,0.5390625,0.9296875,0.9453125,0.5390625,0.9765625,0.8671875,0.6640625,0.4453125,0.7265625,0.4921875,0.4765625,0.6328125,0.7890625,0.0546875,0.5859375,0.4140625,0.4765625,0.7265625,0.8515625,0.8515625,0.1328125,0.8359375,0.3828125,0.3515625,0.3671875,0.7109375,0.5234375,0.1015625,0.0234375,0.2265625,0.7265625,0.2421875,0.4453125,0.9453125,0.5703125,0.8046875,0.9921875,0.8828125,0.2734375,0.9453125,0.6640625,0.1328125,0.2421875,0.8984375,0.7421875,0.4140625,0.4453125,0.6484375,0.6953125,0.6484375,0.3828125,0.3984375,0.6328125,0.5546875,0.5390625,0.3203125,0.4296875,0.2734375,0.6640625,0.8203125,0.4609375,0.8828125,0.5390625,0.5078125,0.1953125,0.3984375,0.1171875,0.2578125,0.6015625,0.8203125,0.8515625,0.8984375,0.4296875,0.4453125,0.3515625,0.2890625,0.0859375,0.8671875,0.6953125,0.6171875,0.6484375,0.6796875,0.0234375,0.1953125,0.2421875,0.2734375,0.7109375,0.8203125,0.4765625,0.5078125,0.3984375,0.5546875,0.3203125,0.8046875,0.2578125,0.6640625,0.1484375,0.6796875,0.1171875,0.7109375,0.1328125,0.5859375,0.0703125,0.2109375,0.7109375,0.2578125,0.7578125,0.8203125,0.4453125,0.8046875,0.3828125,0.8359375,0.6171875,0.8984375,0.1015625,0.1796875,0.5859375,0.6953125,0.4921875,0.2890625,0.4921875,0.9453125,0.6796875,0.1953125,0.8046875,0.6484375,0.2734375,0.6640625,0.9296875,0.3359375,0.7890625,0.9609375,0.4453125,0.8984375,0.3046875,0.1171875,0.5859375,0.2578125,0.9140625,0.2734375,0.8828125,0.4296875,0.6796875,0.9765625,0.8359375,0.5078125,0.0859375,0.8203125,0.4140625,0.7578125,0.1015625,0.5546875,0.6953125,0.9453125,0.5234375,0.8828125,0.8203125,0.0234375,0.3828125,0.0546875,0.0703125,0.1328125,0.5390625,0.4140625,0.4140625,0.5234375,0.5078125,0.2421875,0.6484375,0.7578125,0.2265625,0.6953125,0.1015625,0.8359375,0.4140625,0.9765625,0.7890625,0.1328125,0.6953125,0.8984375,0.6171875,0.9296875,0.6015625,0.3984375,0.4140625,0.5234375,0.3828125,0.5546875,0.0078125,0.6640625,0.5546875,0.6953125,0.8046875,0.6484375,0.1796875,0.2265625,0.6796875,0.5234375,0.2109375,0.4140625,0.0078125,0.7578125,0.9609375,0.7265625,0.4453125,0.6328125,0.2421875,0.5859375,0.1484375,0.2109375,0.2421875,0.2734375,0.8984375,0.0859375,0.1328125,0.0234375,0.8984375,0.4921875,0.6171875,0.0703125,0.2890625,0.2109375,0.6484375,0.9609375,0.8046875,0.7421875,0.2734375,0.1015625,0.0390625,0.8046875,0.2890625,0.3359375,0.6640625,0.8515625,0.6953125,0.5078125,0.4921875,0.1640625,0.5234375,0.5859375,0.1015625,0.8828125,0.0234375,0.0859375,0.6328125,0.4921875,0.7421875,0.7890625,0.5546875,0.9296875,0.7734375,0.1328125,0.3828125,0.5234375,0.9453125,0.8203125,0.0078125,0.2578125,0.8359375,0.6171875,0.5703125,0.6640625,0.1484375,0.3515625,0.4140625,0.9609375,0.1484375,0.5703125,0.7265625,0.3046875,0.6171875,0.4765625,0.0390625,0.8046875,0.5546875,0.6796875,0.5546875,0.9765625,0.4609375,0.9765625,0.9296875,0.9296875,0.5703125,0.8671875,0.6484375,0.7421875,0.7109375,0.1484375,0.0390625,0.8828125,0.3828125,0.7421875,0.7578125,0.0703125,0.4765625,0.2734375,0.9296875,0.4765625,0.3671875,0.1328125,0.1640625,0.5390625,0.0078125,0.8828125,0.0546875,0.2890625,0.0390625,0.9453125,0.8515625,0.9921875,0.4140625,0.2578125,0.3203125,0.8359375,0.0078125,0.3828125,0.8359375,0.7109375,0.7734375,0.1328125,0.6953125,0.5390625,0.4453125,0.0390625,0.1015625,0.3203125,0.0390625,0.2578125,0.0390625,0.6015625,0.2421875,0.3671875,0.9296875,0.3359375,0.6796875,0.9140625,0.3203125,0.0390625,0.8671875,0.8828125,0.9921875,0.9453125,0.5546875,0.9140625,0.3203125,0.7890625,0.0234375,0.1171875,0.9765625,0.6953125,0.3984375,0.3828125,0.6640625,0.8203125,0.3984375,0.1953125,0.2265625,0.6328125,0.3828125,0.2265625,0.7109375,0.0859375,0.7578125,0.5078125,0.6796875,0.7109375,0.1484375,0.6953125,0.6171875,0.2578125,0.1953125,0.5078125,0.4140625,0.9921875,0.8359375,0.5546875,0.7578125,0.6171875,0.6796875,0.1171875,0.4609375,0.8046875,0.1796875,0.4609375,0.8046875,0.1328125,0.6796875,0.4921875,0.8359375,0.9921875,0.3515625,0.1953125,0.5703125,0.4921875,0.2734375,0.9765625,0.5703125,0.7578125,0.7109375,0.7421875,0.3203125,0.2734375,0.3203125,0.0234375,0.4453125,0.8828125,0.4921875,0.6640625,0.3046875,0.2265625,0.4921875,0.4609375,0.3984375,0.1171875,0.0078125,0.3828125,0.0234375,0.7890625,0.7109375,0.2109375,0.2265625,0.1796875,0.4921875,0.3046875,0.4140625,0.1953125,0.4296875,0.3671875,0.1796875,0.9765625,0.2890625,0.8515625,0.8984375,0.7265625,0.5546875,0.2109375,0.3984375,0.3359375,0.4140625,0.8671875,0.7265625,0.2578125,0.9453125,0.6796875,0.1484375,0.2421875,0.1640625,0.5234375,0.2421875,0.4453125,0.4765625,0.2421875,0.3203125,0.3671875,0.3203125,0.5234375,0.2890625,0.9140625,0.1171875,0.6484375,0.9765625,0.1953125,0.9140625,0.8359375,0.7890625,0.2734375,0.3671875,0.2890625,0.5859375,0.1328125,0.6796875,0.2421875,0.3515625,0.4296875,0.4609375,0.7890625,0.0234375,0.9296875,0.4296875,0.8046875,0.2421875,0.1015625,0.2734375,0.8828125,0.4140625,0.6328125,0.2265625,0.0546875,0.7734375,0.2578125,0.3984375,0.8671875,0.7109375,0.5703125,0.0859375,0.1171875,0.9609375,0.3984375,0.5703125,0.0078125,0.6640625,0.4609375,0.1015625,0.7578125,0.3046875,0.6328125,0.0078125,0.9296875,0.9296875,0.9609375,0.2890625,0.3046875,0.1171875,0.7265625,0.3515625,0.9296875,0.3828125,0.3515625,0.8828125,0.9296875,0.5859375,0.6953125,0.6796875,0.2578125,0.9765625,0.1171875,0.1796875,0.5703125,0.5390625,0.9765625,0.0234375,0.8828125,0.3203125,0.0859375,0.1015625,0.6484375,0.8359375,0.2890625,0.9140625,0.4609375,0.6953125,0.5390625,0.0703125,0.9609375,0.3515625,0.9296875,0.2734375,0.8671875,0.6328125,0.4765625,0.3515625,0.8828125,0.1484375,0.6015625,0.7890625,0.0078125,0.8359375,0.3046875,0.2265625,0.2578125,0.6015625,0.6640625,0.8515625,0.9140625,0.7109375,0.4765625,0.0703125,0.1640625,0.0703125,0.6171875,0.8203125,0.7109375,0.0859375,0.5234375,0.1953125,0.1328125,0.2578125,0.5234375,0.3984375,0.6796875,0.3515625,0.6015625,0.7265625,0.7109375,0.5546875,0.5078125,0.6484375,0.3828125,0.1796875,0.1328125,0.6171875,0.0546875,0.5390625,0.8984375,0.2265625,0.8046875,0.5859375,0.7265625,0.1640625,0.2734375,0.3984375,0.5390625,0.9296875,0.6953125,0.9453125,0.8984375,0.1640625,0.0546875,0.6484375,0.3984375,0.8046875,0.1171875,0.6953125,0.4765625,0.8046875,0.2109375,0.6015625,0.1953125,0.1953125,0.1953125,0.7890625,0.0234375,0.5078125,0.1015625,0.3515625,0.6328125,0.5546875,0.0078125,0.9921875,0.4453125,0.8984375,0.0390625,0.3515625,0.9921875,0.8828125,0.7890625,0.9609375,0.0390625,0.6171875,0.8046875,0.8828125,0.3671875,0.6484375,0.1171875,0.2109375,0.1640625,0.8046875,0.7734375,0.6015625,0.3203125,0.7265625,0.2109375,0.6015625,0.6171875,0.4921875,0.5703125,0.7734375,0.1015625,0.6328125,0.3828125,0.1484375,0.3984375,0.3203125,0.4453125,0.4296875,0.3828125,0.9140625,0.8828125,0.9296875,0.5703125,0.6640625,0.0859375,0.5703125,0.1328125,0.6796875,0.9765625,0.8984375,0.8359375,0.5859375,0.4609375,0.8203125,0.3203125,0.3203125,0.5390625,0.2890625,0.7890625,0.3828125,0.4453125,0.3828125,0.3828125,0.8984375,0.2109375,0.3515625,0.4296875,0.5703125,0.4765625,0.0234375,0.5703125,0.8828125,0.3046875,0.7578125,0.7578125,0.2578125,0.2109375,0.5546875,0.5703125,0.3984375,0.3203125,0.9453125,0.5703125,0.8828125,0.4765625,0.7421875,0.5078125,0.2109375,0.0234375,0.7265625,0.9609375,0.6953125,0.3828125,0.3359375,0.5390625,0.6796875,0.0859375,0.6015625,0.2265625,0.1640625,0.7109375,0.0546875,0.3828125,0.0546875,0.7890625,0.7109375,0.5390625,0.1171875,0.4609375,0.5390625,0.4765625,0.8984375,0.9765625,0.3203125,0.7421875,0.2421875,0.7109375,0.7421875,0.0234375,0.1484375,0.3984375,0.9609375,0.3203125,0.4296875,0.3359375,0.5546875,0.2421875,0.1015625,0.8828125,0.9921875,0.1328125,0.3671875,0.8515625,0.9453125,0.5546875,0.9296875};
    double error = 0;
    for (std::size_t i = 0 ; i < dim_num ; ++i)
    {
        error += std::abs(quasi1[i]-refvalues[i]);
    }
    const double tolerance = 1e-10;
    if (error < tolerance)
    {
        os << "SUCCEEDED" << std::endl;
        return true;
    }
    else
    {
        os << "FAILED" << std::endl;
        return false;
    }
}

bool RegressionTest::DebyeFunction(std::ostream &os) const
{
    std::size_t k = 1;
    std::vector<std::pair<double, double> > dXY;
    double refValues[] = {100.997303049997,50.9947867957852,34.3256260997606,25.989808459669,20.9873313748562,17.6515273448792,15.2681102978792,13.4799371976749,12.0885952461267,10.9750367640828,10.0635041372635,9.30349228920349,8.66003616668244,8.10816073139932,7.62955095497732,7.21047056584182,6.84041535602381,6.51121538569554,6.2164207020633,5.95087134259248,5.710390194454,5.49155961957625,5.2915563514227,5.10802766757512,4.93899728089677,4.78279294811961,4.63799016541203,4.50336792918219,4.37787364981854,4.26059508268233,4.15073769181121,4.04760625792842,3.95058983045043,3.85914933502253,3.77280730547698,3.69113932713153,3.61376686766107,3.54035123993704,3.47058849366072,3.4042050732516,3.3409541111667,3.28061225074578,3.22297691238042,3.16786393247831,3.1151055172323,3.06454846328915,3.01605260556699,2.96948945909559,2.92474102716197,2.88169875247854,2.84026259174318,2.800340196981,2.76184618956431,2.72470151489706,2.68883286749743,2.65417217767871,2.62065615226373,2.58822586281168,2.5568263757202,2.5264064193172,2.49691808369788,2.46831654960968,2.44055984315784,2.41360861350727,2.38742593110427,2.36197710424181,2.33722951205173,2.31315245223302,2.28971700202109,2.26689589107403,2.24466338510081,2.22299517918729,2.20186829988983,2.18126101526733,2.1611527521108,2.14152401970733,2.12235633954466,2.10363218042304,2.08533489849533,2.06744868180419,2.04995849892752,2.03285005138169,2.01610972946542,1.99972457125779,1.98368222451041,1.96797091119843,1.95257939451618,1.93749694812326,1.92271332746389,1.90821874299826,1.894003835199,1.88005965117823,1.86637762282258,1.85294954632392,1.8397675630028,1.82682414133057,1.81411206006347,1.80162439240933,1.78935449115397,1.77729597467997,1.76544237989103,1.75378849028429,1.74232830640102,1.73105638498422,1.71996748985041,1.70905658211987,1.69831881099482,1.68774950504992,1.67734416400222,1.66709845092999,1.65700818491225,1.64706933406256,1.63727800893274,1.6276304562638,1.6181230530629,1.60875230098668,1.5995148210127,1.59040734838174,1.58142672779526,1.57256990885287,1.56383394171616,1.55521597298573,1.54671324177941,1.53832307600024,1.53004288878356,1.5218701751134,1.51380250859866,1.50583753840042,1.49797298630225,1.49020664391571,1.48253637001382,1.47496008798585,1.46747578340683,1.460081501716,1.45277534599842,1.44555547486443,1.43842010042208,1.4313674863376,1.4243959459798,1.41750384064377,1.41068957785041,1.40395160971765,1.39728843140017,1.39069857959399,1.38418063110313,1.37773320146501,1.37135494363213,1.36504454670708,1.35880073472862,1.35262226550621,1.34650792950097,1.34045654875076,1.33446697583745,1.32853809289446,1.32266881065268,1.31685806752316,1.31110482871481,1.30540808538566,1.29976685382617,1.29418017467312,1.28864711215286,1.28316675335262,1.27773820751856,1.27236060537962,1.26703309849594,1.26175485863078,1.2565250771451,1.25134296441375,1.24620774926237,1.24111867842421,1.236075016016,1.23107604303215,1.22612105685643,1.22120937079061,1.21634031359915,1.21151322906953,1.20672747558742,1.20198242572626,1.19727746585047,1.1926119957321,1.18798542817998,1.18339718868129,1.17884671505477,1.17433345711534,1.16985687634949,1.16541644560132,1.16101164876847,1.15664198050793,1.15230694595112,1.14800606042797,1.14373884919971,1.13950484720003,1.13530359878423,1.13113465748622,1.12699758578297,1.12289195486613,1.11881734442076,1.11477334241057,1.11075954486985,1.10677555570149,1.10282098648114,1.09889545626716,1.09499859141616,1.09113002540406,1.08728939865234,1.08347635835931,1.07969055833642,1.07593165884914,1.07219932646257,1.06849323389131,1.06481305985376,1.06115848893044,1.05752921142635,1.05392492323724,1.05034532571952,1.04679012556391,1.04325903467247,1.03975177003912,1.03626805363342,1.03280761228745,1.0293701775859,1.025955485759,1.02256327757849,1.0191932982562,1.01584529734552,1.01251902864538,1.00921425010682,1.005930723742,1.00266821553563,0.999426495358694,0.996205336884441,0.993004517506534,0.989823818259326,0.986663023740189,0.983521922033824,0.980400304638505,0.977297966394199,0.974214705412503,0.971150323008341,0.968104623633384,0.965077414811123,0.962068507073566,0.9590777138995,0.956104851654276,0.953149739531075,0.950212199493619,0.947292056220263,0.944389137049461,0.941503271926544,0.938634293351783,0.935782036329693,0.932946338319558,0.930127039187128,0.927323981157466,0.924537008768904,0.921765968828087,0.919010710366075,0.91627108459546,0.913546944868491,0.910838146636167,0.90814454740827,0.905466006714326,0.902802386065455,0.900153548917096,0.897519360632575,0.894899688447504,0.892294401434987,0.889703370471595,0.887126468204123,0.884563569017076,0.882014549000884,0.879479285920816,0.876957659186596,0.874449549822669,0.871954840439133,0.869473415203299,0.867005159811877,0.864549961463758,0.862107708833394,0.859678292044741,0.857261602645774,0.854857533583535,0.852465979179721,0.850086835106794,0.847719998364583,0.845365367257398,0.84302284137161,0.840692321553711,0.838373709888829,0.836066909679688,0.833771825426009,0.831488362804334,0.829216428648266,0.826955930929118,0.824706778736952,0.822468882262015,0.820242152776537,0.818026502616916,0.815821845166251,0.813628094837224,0.811445167055342,0.809272978242496,0.807111445800855,0.804960488097085,0.802820024446872,0.800689975099756,0.79857026122426,0.796460804893317,0.794361529069972,0.792272357593372,0.79019321516502,0.788124027335307,0.786064720490289,0.784015221838728,0.781975459399381,0.77994536198853,0.777924859207747,0.775913881431901,0.773912359797377,0.771920226190534,0.769937413236366,0.767963854287386,0.765999483412714,0.764044235387364,0.762098045681739,0.760160850451315,0.758232586526514,0.756313191402769,0.754402603230767,0.752500760806873,0.750607603563728,0.748723071561014,0.746847105476396,0.744979646596616,0.743120636808761,0.74127001859167,0.739427735007515,0.737593729693517,0.735767946853817,0.733950331251489,0.732140828200695,0.730339383558976,0.728545943719686,0.726760455604548,0.724982866656347,0.723213124831752,0.721451178594254,0.71969697690724,0.717950469227171,0.716211605496889,0.714480336139036,0.712756612049583,0.711040384591472,0.709331605588367,0.707630227318507,0.705936202508667,0.704249484328222,0.702570026383302,0.700897782711061,0.699232707774022,0.697574756454535,0.695923884049312,0.694280046264066,0.692643199208224,0.691013299389744,0.689390303709999,0.687774169458762,0.68616485430926,0.684562316313314,0.682966513896558,0.681377405853737,0.679794951344073,0.678219109886718,0.676649841356267,0.675087105978355,0.673530864325312,0.671981077311899,0.670437706191101,0.668900712549997,0.667370058305685,0.665845705701279,0.664327617301962,0.662815755991109,0.661310084966461,0.659810567736367,0.658317168116077,0.656829850224099,0.655348578478606,0.653873317593903,0.652404032576945,0.650940688723909,0.64948325161682,0.648031687120225,0.646585961377921,0.64514604080973,0.64371189210832,0.642283482236083,0.640860778422047,0.639443748158844,0.638032359199721,0.636626579555591,0.635226377492132,0.633831721526926,0.632442580426646,0.631058923204275,0.629680719116372,0.628307937660378,0.626940548571956,0.625578521822378,0.624221827615938,0.622870436387417,0.621524318799571,0.620183445740662,0.618847788322023,0.617517317875658,0.616192005951874,0.614871824316949,0.613556744950834,0.612246740044882,0.610941781999613,0.609641843422513,0.608346897125854,0.607056916124558,0.605771873634075,0.604491743068307,0.603216498037547,0.601946112346451,0.600680559992043,0.599419815161738,0.598163852231399,0.596912645763416,0.595666170504817,0.594424401385397,0.593187313515877,0.591954882186085,0.590727082863166,0.589503891189811,0.588285282982511,0.587071234229835,0.585861721090731,0.584656719892846,0.583456207130876,0.582260159464927,0.581068553718908,0.579881366878935,0.578698576091765,0.577520158663244,0.576346092056774,0.575176353891812,0.574010921942367,0.572849774135538,0.571692888550058,0.570540243414856,0.569391817107646,0.568247588153528,0.567107535223602,0.565971637133613,0.564839872842599,0.563712221451564,0.562588662202162,0.561469174475408,0.560353737790389,0.559242331803005,0.558134936304721,0.557031531221328,0.555932096611728,0.554836612666733,0.553745059707871,0.552657418186213,0.551573668681217,0.550493791899577,0.54941776867409,0.548345579962543,0.547277206846601,0.546212630530719,0.54515183234106,0.544094793724431,0.543041496247228,0.541991921594393,0.540946051568388,0.539903868088176,0.538865359701988,0.537830495468707,0.536799264227715,0.535771648354036,0.534747630334286,0.53372719276572,0.5327103183553,0.531696989918762,0.530687190379708,0.529680902768689,0.528678110222321,0.527678795982391,0.526682943394986,0.525690535909624,0.524701557078403,0.52371599055515,0.522733820094585,0.521755029551494,0.520779602879912,0.51980752413231,0.518838777458797,0.517873347106326,0.516911217417915,0.515952372831867,0.514996797881006,0.514044477191922,0.513095395484215,0.51214953756976,0.511206888351967,0.510267432825063,0.509331156073363,0.508398043270571,0.507468079679069,0.506541250649225,0.505617541618703,0.504696938111784,0.503779425738692,0.502864990194925,0.501953617260597,0.501045292799786,0.500140002759885,0.499237733170964,0.498338470145137,0.497442199875936,0.496548908637692,0.495658582784916,0.494771208751698,0.493886773051102,0.493005262274572,0.492126663091343,0.491250962247856,0.490378146567182,0.48950820294845,0.488641118366282,0.487776879870229,0.486915474584222,0.486056889706016,0.485201112506651,0.484348130329914,0.4834979305918,0.482650500779987,0.481805828453318,0.480963901241273,0.480124706843464,0.479288233029125,0.478454467636608,0.477623398572884,0.476795013813052,0.475969301399849,0.475146249443165,0.474325846119564,0.473508079671811,0.472692938408397,0.471880410703078,0.471070484994408,0.470263149785287,0.469458393642505,0.468656205196291,0.467856573139871,0.467059486229029,0.466264933281665,0.465472903177367,0.46468338485698,0.463896367322183,0.463111839635065,0.462329790917711,0.46155021035179,0.460773087178139,0.459998410696364,0.459226170264434,0.458456355298283,0.457688955271417,0.456923959714518,0.456161358215061,0.455401140416927,0.454643296020019,0.45388781477989,0.453134686507363,0.452383901068164,0.451635448382551,0.45088931842495,0.450145501223593,0.44940398686016,0.448664765469425,0.447927827238901,0.44719316240849,0.446460761270141,0.445730614167502,0.445002711495582,0.444277043700414,0.443553601278718,0.44283237477757,0.442113354794074,0.441396531975034,0.440681897016632,0.439969440664105,0.43925915371143,0.438551027001005,0.437845051423338,0.437141217916737,0.436439517467001,0.435739941107116,0.435042479916949,0.434347125022954,0.433653867597867,0.432962698860416,0.432273610075025,0.431586592551526,0.430901637644867,0.430218736754831,0.429537881325747,0.428859062846213,0.428182272848814,0.427507502909847,0.426834744649047,0.42616398972931,0.42549522985643,0.424828456778822,0.424163662287265,0.42350083821463,0.422839976435626,0.422181068866532,0.421524107464944,0.420869084229521,0.420215991199725,0.419564820455576,0.418915564117394,0.418268214345562,0.417622763340269,0.416979203341273,0.416337526627654,0.41569772551758,0.41505979236806,0.414423719574713,0.413789499571534,0.413157124830653,0.412526587862115,0.411897881213639,0.411270997470399,0.410645929254791,0.410022669226214,0.409401210080843,0.408781544551409,0.408163665406982,0.407547565452748,0.406933237529797,0.406320674514907,0.40570986932033,0.405100814893582,0.404493504217231,0.40388793030869,0.40328408622001,0.402681965037674,0.402081559882393,0.401482863908904,0.40088587030577,0.400290572295178,0.399696963132742,0.399105036107307,0.398514784540754,0.397926201787806,0.397339281235832,0.396754016304662,0.396170400446394,0.395588427145203,0.395008089917161,0.394429382310044,0.393852297903153,0.393276830307126,0.392702973163761,0.392130720145832,0.391560064956914,0.390991001331199,0.390423523033324,0.389857623858192,0.389293297630802,0.388730538206073,0.388169339468671,0.387609695332843,0.387051599742241,0.38649504666976,0.385940030117367,0.385386544115936,0.384834582725082,0.384284140033,0.383735210156301,0.383187787239848,0.382641865456601,0.38209743900745,0.381554502121066,0.381013049053736,0.380473074089211,0.37993457153855,0.379397535739965,0.378861961058671,0.378327841886729,0.377795172642901,0.377263947772496,0.37673416174722,0.376205809065035,0.375678884250003,0.375153381852147,0.374629296447303,0.374106622636976,0.373585355048197,0.373065488333383,0.372547017170193,0.372029936261387,0.371514240334692,0.370999924142658,0.370486982462523,0.369975410096076,0.36946520186952,0.368956352633341,0.36844885726217,0.367942710654651,0.36743790773331,0.366934443444421,0.366432312757881,0.365931510667073,0.365432032188743,0.364933872362868,0.364437026252531,0.363941488943798,0.363447255545582,0.362954321189532,0.362462681029896,0.361972330243408,0.36148326402916,0.360995477608482,0.360508966224821,0.360023725143622,0.359539749652206,0.359057035059656,0.358575576696693,0.358095369915567,0.357616410089931,0.357138692614734,0.356662212906102,0.356186966401226,0.355712948558243,0.355240154856132,0.354768580794597,0.354298221893953,0.353829073695022,0.353361131759019,0.352894391667444,0.35242884902197,0.351964499444343,0.351501338576266,0.351039362079299,0.35057856563475,0.350118944943568,0.349660495726244,0.349203213722703,0.3487470946922,0.348292134413221,0.347838328683378,0.347385673319308,0.346934164156573,0.34648379704956,0.346034567871382,0.345586472513775,0.345139506887006,0.34469366691977,0.344248948559095,0.343805347770247,0.343362860536631,0.342921482859696,0.342481210758843,0.342042040271328,0.341603967452169,0.341166988374054,0.340731099127246,0.340296295819495,0.339862574575942,0.339429931539032,0.338998362868419,0.338567864740883,0.338138433350234,0.337710064907227,0.337282755639474,0.336856501791353,0.336431299623926,0.336007145414847,0.33558403545828,0.335161966064811,0.334740933561364,0.334320934291114,0.33390196461341,0.333484020903681,0.333067099553361,0.332651196969804,0.332236309576201,0.331822433811498,0.331409566130317,0.330997703002873,0.330586840914896,0.33017697636755,0.329768105877354,0.329360225976102,0.328953333210786,0.328547424143518,0.328142495351454,0.327738543426714,0.327335564976305,0.326933556622052,0.326532515000511,0.326132436762905,0.325733318575041,0.325335157117241,0.324937949084264,0.324541691185236,0.324146380143576,0.323752012696921,0.323358585597056,0.322966095609843,0.322574539515148,0.322183914106769,0.32179421619237,0.321405442593405,0.321017590145052,0.320630655696143,0.320244636109094,0.319859528259838,0.319475329037757,0.319092035345609,0.318709644099471,0.31832815222866,0.317947556675677,0.317567854396132,0.317189042358686,0.316811117544979,0.316434076949568,0.316057917579862,0.315682636456059,0.315308230611077,0.314934697090497,0.314562032952494,0.31419023526778,0.313819301119534,0.313449227603346,0.313080011827152,0.312711650911175,0.31234414198786,0.311977482201817,0.311611668709758,0.311246698680438,0.310882569294595,0.310519277744891,0.310156821235851,0.309795196983806,0.309434402216835,0.309074434174706,0.308715290108816,0.308356967282137,0.307999462969157,0.307642774455825,0.307286899039491,0.306931834028852,0.306577576743897,0.30622412451585,0.305871474687114,0.305519624611218,0.30516857165276,0.304818313187355,0.30446884660158,0.304120169292918,0.30377227866971,0.303425172151096,0.303078847166964,0.3027333011579,0.302388531575131,0.302044535880478,0.301701311546302,0.301358856055449,0.301017166901205,0.300676241587243,0.30033607762757,0.299996672546479,0.299658023878497,0.29932012916834,0.298982985970857,0.298646591850986,0.2983109443837,0.297976041153965,0.297641879756684,0.297308457796656,0.296975772888524,0.296643822656725,0.29631260473545,0.295982116768591,0.295652356409694,0.295323321321917,0.294995009177979,0.294667417660117,0.294340544460037,0.294014387278873,0.293688943827135,0.293364211824673,0.293040189000622,0.292716873093365,0.292394261850486,0.292072353028725,0.291751144393934,0.291430633721037,0.291110818793982,0.290791697405699,0.290473267358059,0.290155526461831,0.289838472536635,0.289522103410907,0.289206416921851,0.288891410915399,0.288577083246171,0.288263431777433,0.287950454381054,0.287638148937466,0.287326513335625,0.287015545472968,0.286705243255375,0.286395604597126,0.286086627420866,0.28577830965756,0.285470649246456,0.285163644135047,0.284857292279031,0.284551591642269,0.284246540196754,0.283942135922564,0.283638376807831,0.283335260848697,0.283032786049281,0.282730950421641,0.282429751985731,0.282129188769371,0.281829258808208,0.281529960145676,0.281231290832963,0.280933248928973,0.28063583250029,0.280339039621143,0.280042868373368,0.279747316846376,0.279452383137113,0.279158065350028,0.278864361597037,0.278571269997489,0.278278788678129,0.277986915773066,0.277695649423737,0.277404987778874,0.27711492899447,0.276825471233743,0.276536612667107,0.276248351472132,0.275960685833517,0.275673613943054,0.275387133999596,0.275101244209022,0.274815942784208,0.274531227944991,0.274247097918141,0.273963550937324,0.273680585243074,0.273398199082759,0.273116390710552,0.272835158387396,0.272554500380976,0.272274414965686,0.271994900422599,0.271715955039436,0.271437577110535,0.271159764936822,0.27088251682578,0.270605831091416,0.270329706054236,0.270054140041213,0.269779131385756,0.269504678427683,0.26923077951319,0.268957432994821,0.268684637231442,0.268412390588209,0.268140691436541,0.267869538154093,0.267598929124721,0.267328862738463,0.267059337391504,0.26679035148615,0.266521903430801,0.266253991639921,0.265986614534014,0.265719770539595,0.265453458089159,0.26518767562116,0.264922421579981,0.264657694415906,0.264393492585096};
    Maths::DebyeFunction debyeFunction;
    double error = 0.0;
    int i = 0 ;
    for (double x = 0.01 ; x < 10.0 ; x += 0.01, ++i)
    {
        error += std::abs(refValues[i] - debyeFunction(x, k));
    }
    const double tolerance = 1e-10;
    if (error < tolerance)
    {
        os << "SUCCEEDED" << std::endl;
        return true;
    }
    else
    {
        os << "FAILED" << std::endl;
        return false;
    }
}

/////////////////////////////////////////////////////
//
//      Regression test launcher
//
/////////////////////////////////////////////////////

void RegressionTestLauncher::FillMap()
{
    m_mapping.insert(std::make_pair("Analytic", &RegressionTest::AnalyticFormulae));
    m_mapping.insert(std::make_pair("VolatilitySurface", &RegressionTest::VolatilitySurfaceInterpolation));
    m_mapping.insert(std::make_pair("Date", &RegressionTest::Date));
    m_mapping.insert(std::make_pair("Process Path Simulation", &RegressionTest::ProcessPathSimulation));
    m_mapping.insert(std::make_pair("Payoff linearization", &RegressionTest::PayoffLinearization));
    m_mapping.insert(std::make_pair("Interpolation", &RegressionTest::Interpolation));
    m_mapping.insert(std::make_pair("Time Statistics", &RegressionTest::TimeStatistics));
    m_mapping.insert(std::make_pair("Bond pricing", &RegressionTest::BondPricing));
    m_mapping.insert(std::make_pair("Matrix inversion", &RegressionTest::MatrixInversion));
    m_mapping.insert(std::make_pair("Newton Solver", &RegressionTest::NewtonSolver));
    m_mapping.insert(std::make_pair("Ticker", &RegressionTest::Ticker));
    m_mapping.insert(std::make_pair("Sobol", &RegressionTest::Sobol));
    m_mapping.insert(std::make_pair("Debye Function", &RegressionTest::DebyeFunction));
}

RegressionTestLauncher::RegressionTestLauncher(std::ostream & out) : m_out(out)
{
    FillMap();
}

bool RegressionTestLauncher::Launch() const
{
    bool result = true;
    
    //  Iterate along the map
    auto it = m_mapping.begin();
    for ( ; it != m_mapping.end() ; ++it)
    {
        m_out << "Regression Test " << it->first << std::endl;
        result = (m_regTest.*(it->second))(m_out);
        if (!result)
        {
            return result;
        }
        std::cout << std::endl;
    }
    return result;
}