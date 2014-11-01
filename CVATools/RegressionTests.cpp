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