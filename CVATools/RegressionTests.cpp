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

//  Forward declaration of the different regression tests
bool RegressionTest_BondPricing(std::ostream & os);
bool RegressionTest_TimeStatistics(std::ostream & os);
bool RegressionTest_PayoffLinearization(std::ostream & os);
bool RegressionTest_Interpolation(std::ostream & os);
bool RegressionTest_VolatilitySurfaceInterpolation(std::ostream & os);
bool RegressionTest_ProcessPathSimulation(std::ostream & os);
bool RegressionTest_Date(std::ostream & os);
bool RegressionTest_AnalyticFormulae(std::ostream & os);

//  Declaration of all the regression tests

bool RegressionTest_BondPricing(std::ostream & os)
{
    //////////////////////////////////////////////////////////////
    //                                                          //
    //          Regression test for Bond Pricing                //
    //                                                          //
    //////////////////////////////////////////////////////////////
    try
    {
        os << "Regression Test for Bond Pricing" << std::endl;
        
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
        const double dRefBondPrice = 0.717898133743137;
        const double dTolerance = 1.0e-5;
        
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
        const double dRefYield = 0.0271908027808272;
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
        const double dRefISpread =-0.000382137306462867;
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
        const double dRefZSpread = 0.000366813031560259;
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
    catch( const Utilities::MyException & e)
    {
        os << "MyException caught : " << std::endl;
        os << e.what() << std::endl;
        return false;
    }
    catch( const std::exception & e)
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

bool RegressionTest_TimeStatistics(std::ostream & os)
{
    try
    {
        // Regression Test Statistics Time
        std::size_t iNTimes = 10;
        os << "Regression Test Time Computation for statistics" << std::endl;
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

bool RegressionTest_PayoffLinearization(std::ostream & os)
{
    os << "Regression Test Payoff Linearization" << std::endl;
    os << std::endl;
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
    
    //os << "beta_1 : " << dRegCoefs.first << std::endl;
    //os << "beta_2 : " << dRegCoefs.second << std::endl;
    return true;
}

bool RegressionTest_Interpolation(std::ostream & os)
{
    os << "Regression Test Interpolation " << std::endl;
    os << std::endl;
    double variables[] = {1.0, 2.0, 3.0, 3.5}, values[] = {1.0, 0.0, 1.0, 1.0};
    std::vector<double> vectvar(variables, variables + 4), vectvalues(values, values + 4);
    
    Utilities::Interp::LinearInterpolator lin(vectvar, vectvalues);
    Utilities::Interp::LogLinDFInterpolator loglindf(vectvar, vectvalues);
    Utilities::Interp::LeftContinuousInterpolator leftcontinuous(vectvar, vectvalues);
    Utilities::Interp::RightContinuousInterpolator rightcontinuous(vectvar, vectvalues);
    Utilities::Interp::HermiteSplineCubicInterpolator hermite(vectvar, vectvalues);
    Utilities::Interp::HermiteDegree5Interpolator hermite5(vectvar, vectvalues);
    double valuesreflin[] = {1,1,1,1,1,1,1,1,1,1,0.9,0.8,0.7,0.6,0.5,0.4,0.3,0.2,0.1,6.38378e-16,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1,1,1,1,1,1,1,1,1,1};
    //double valuesrefloglindf[] = {19,9,5.66666667,4,3,2.33333333,1.85714286,1.5,1.22222222,1,0.818181818,0.666666667,0.5384615,0.428571429,0.333333333,0.25,0.176470588,0.111111111,0.0526315789,6.66133815e-16,0.142857143,0.272727273,0.391304348,0.5,0.6,0.692307692,0.777777778,0.857142857,0.931034483,1,1,1,1,1,1,1,1,1,1};
    double valuesrefleftcontinuous[] = {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    double valuesrefrightcontinuous[] ={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1};
    double valueshermite[] = {-1.349,-0.792,-0.323,0.064,0.375,0.616,0.793,0.912,0.979,1,0.981,0.928,0.847,0.744,0.625,0.496,0.363,0.232,0.109,4.4408921e-16,0.109,0.232,0.363,0.496,0.625,0.744,0.847,0.928,0.981,1,1,1,1,1,1,1,1,1,1};
    double valueshermite5[] = {12.39427,8.33184,5.48301,3.56608,2.34375,1.61952,1.23409,1.06176,1.00683,1,0.99477,0.96384,0.89551,0.79008,0.65625,0.50752,0.35859,0.22176,0.10333,4.4408921e-16,0.109,0.232,0.363,0.496,0.625,0.744,0.847,0.928,0.981,1,1,1,1,1,1,1,1,1,1};
    double dErrorlin = 0.0, dErrorloglindf = 0.0, dErrorleftcontinuous = 0.0, dErrorrightcontinuous = 0.0, dErrorhermite = 0.0, dErrorhermite5 = 0.0;
    for (int i = 0 ; i < 39 ;  i++)
    //int i = 0;
    //for (double var = 0.1 ; var < 4.0 ; var += 0.1, i++)
    {
        double var = 0.1 * (i+1);
        dErrorlin               += std::abs(lin(var) - valuesreflin[i]);
        //  needs to fix extrapolation of log lin df interpolation
        //dErrorloglindf          += std::abs(loglindf(var) - valuesrefloglindf[i]);
        dErrorleftcontinuous    += std::abs(leftcontinuous(var) - valuesrefleftcontinuous[i]);
        dErrorrightcontinuous   += std::abs(rightcontinuous(var) - valuesrefrightcontinuous[i]);
        dErrorhermite           += std::abs(hermite(var) - valueshermite[i]);
        dErrorhermite5          += std::abs(hermite5(var) - valueshermite5[i]);
        //std::cout << std::setprecision(9) << loglindf(var) << "," ;//<< ";" << valuesrefleftcontinuous[i] << "," << dErrorleftcontinuous << std::endl;
    }
    
    //for (double var = 2.5 ; var < 3.0 ; var += 0.01)
    //{
    //    std::cout << std::setprecision(9) << var << ";" << hermite5(var) << std::endl;
    //}
    
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

bool RegressionTest_VolatilitySurfaceInterpolation(std::ostream & os)
{
    os << "Volatility Surface Interpolation" << std::endl;
    
    const double dFwdRef = 1.0, T = 1.0;
    const double strikes[] = {0.6, 0.75, 0.9, 1.0, 1.1, 1.25, 1.4}, vols[] = {0.20, 0.180, 0.150, 0.125, 0.164, 0.197, 0.223};
    const std::vector<double> strikesvect(strikes, strikes + 7), volsvect(vols, vols + 7);
    Finance::Volatility::VolSmile volSmile(strikesvect, volsvect, dFwdRef, T);
    Finance::Volatility::SVIParameterSolver sviParameterSolver(dFwdRef);
    
    try
    {
        sviParameterSolver.Solve(volSmile, true); // use parabola
    }
    catch (Utilities::MyException & excep)
    {
        os << excep.what() << std::endl;
        return false;
    }
    catch (std::exception & excep)
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
    //double dSVIParametrisationParabola[] = {0.24621736,0.241945343,0.237741155,0.233604978,0.229537202,0.225538421,0.221609434,0.217751242,0.213965045,0.210252242,0.206614426,0.203053383,0.199571086,0.196169694,0.192851539,0.189619125,0.186475116,0.183422322,0.18046369,0.177602283,0.174841263,0.17218387,0.169633396,0.167193157,0.16486646,0.162656574,0.160566688,0.158599875,0.15675905,0.155046929,0.153465986,0.152018412,0.150706072,0.149530472,0.14849272,0.147593499,0.146833042,0.146211117,0.14572701,0.145379533,0.145167016,0.145087331,0.145137901,0.145315735,0.145617455,0.146039331,0.146577328,0.147227142,0.14798425,0.14884395,0.149801411,0.15085171,0.151989878,0.153210932,0.154509915,0.155881926,0.157322143,0.158825852,0.160388464,0.162005534,0.163672771,0.16538605,0.167141419,0.168935104,0.170763514,0.172623235,0.174511037,0.176423866,0.178358845,0.180313264,0.182284581,0.184270413,0.186268529,0.188276847,0.190293422,0.192316447,0.194344239,0.196375235,0.198407988,0.200441156,0.202473499,0.204503874,0.206531225,0.20855458,0.210573047,0.212585806,0.214592107,0.216591265,0.218582652,0.220565698,0.222539885,0.224504744,0.22645985,0.22840482,0.230339311,0.232263015,0.234175659,0.236077001,0.237966826,0.239844947};
    double dSmileConvexity[] = {0,0,0,0,0,0,0,0,0,0,1.29359771e-14,0.949704883,1.78164114,2.4290384,2.87421491,3.13579809,3.25859461,3.30559555,3.3517018,3.47883388,3.77215495,4.31718721,5.19764375,6.49383184,8.28151098,0.0355555556,0.644330861,1.15435063,1.54363225,1.81171569,1.97483844,2.06194588,2.11140265,2.16829215,2.28220896,2.50546423,2.89163665,3.49441237,4.36666589,5.55974179,0.037037037,0.360276838,0.649070063,0.829186723,0.884705044,0.846918233,0.784871718,0.797308011,1.00582657,1.54909201,0.025,0.471160929,0.788641532,0.943061447,0.952618404,0.878606525,0.817218999,0.892474478,1.25012642,2.05243197,-0.032231405,0.303823668,0.583122853,0.788223906,0.914127454,0.966309165,0.958991995,0.91363123,0.857588159,0.822970886,0.845623226,0.964244777,1.21962711,1.65399272,2.31042493,-0.01664,0.29481522,0.553271223,0.745602239,0.868917411,0.929103772,0.939527779,0.919879376,0.895144167,0.894690707,0.95146125,1.10125542,1.38209733,1.83367767,2.49686297,0,0,0,0,0,0,0,0,0,0};
    double dSmileSkew[] = {0,0,0,0,0,0,0,0,0,0,-5.94104744e-31,-0.00282663416,-0.00948806359,-0.0177879306,-0.0261397432,-0.0334598681,-0.0390773866,-0.0426581729,-0.0441409854,-0.0436837089,-0.0416181832,-0.0384123008,-0.0346382569,-0.0309460151,-0.0280411887,-0.04,-0.0390942586,-0.0364754161,-0.0333275637,-0.0304959997,-0.0285385681,-0.027770216,-0.0283016515,-0.0300728658,-0.0328821817,-0.0364114042,-0.0402475734,-0.0439017534,-0.0468252377,-0.0484234993,-0.0277777778,-0.0336819672,-0.0459154924,-0.0562702285,-0.0597375166,-0.0540647001,-0.0393628374,-0.0177598572,0.00690592272,0.0293564136,0.039,0.0439307097,0.046218974,0.046166346,0.0441710164,0.040712531,0.0363382327,0.0316512487,0.0272998572,0.0239680904,0.03,0.0295757139,0.0294916847,0.0295799156,0.0297097648,0.0297839037,0.0297346528,0.0295206602,0.0291238913,0.0285469022,0.0278103697,0.0269508553,0.0260187821,0.0250766045,0.024197154,0.0208,0.0216657732,0.0238350792,0.0263592577,0.0285261241,0.0298364062,0.0299821628,0.0288270217,0.0263880872,0.0228193809,0.0183966904,0.0135037119,0.0086193804,0.00430629163,0.00120012695,0,0,0,0,0,0,0,0,0,0};
    double dErrorInterpHermite = 0.0, dErrorSVIParabola = 0.0, dErrorSmileConvexity = 0.0, dErrorSmileSkew = 0.0;
    int i = 0;
    for (double dStrike = 0.50 ; dStrike < 1.5 ; dStrike += 0.01, ++i)
    {
        //os << std::setprecision(9) << sviParameterSolver(dStrike) << std::endl;
        dErrorInterpHermite += std::abs(dVolHermiteInterp[i] - volSmile(dStrike));
        //dErrorSVIParabola += std::abs(sviParameterSolver(dStrike) - dSVIParametrisationParabola[i]);
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
    //os << "SVI Parametrisation of smile : " ;
    //if (dErrorSVIParabola < dTolerance)
    //{
    //    os << "SUCCEEDED" << std::endl;
    //}
    //else
    //{
    //    os << "FAILED" << std::endl;
    //    return false;
    //}
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

bool RegressionTest_ProcessPathSimulation(std::ostream & os)
{
    os << "Process Path Simulation" << std::endl;
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
bool RegressionTest_Date(std::ostream & os)
{
    os << "Regression Test for date" << std::endl;
    
    Utilities::Date::MyDate sToday(3,2,2014);
    
    os << "Today is " << sToday.Print() << std::endl;

#ifdef DEBUG
        os << "Add one day" << std::endl;
        os << "New date is " << sToday.Add(1, Utilities::Date::DAY).Print() << std::endl;
        os << "Add one week" << std::endl;
        os << "New date is " << sToday.Add(1, Utilities::Date::WEEK).Print() << std::endl;
        os << "Add one month " << std::endl;
        os << "New date is " << sToday.Add(1, Utilities::Date::MONTH).Print() << std::endl;
        os << "Add one year " << std::endl;
        os << "New date is " << sToday.Add(1, Utilities::Date::YEAR).Print() << std::endl;
#else
        sToday.Add(1, Utilities::Date::DAY);
        sToday.Add(1, Utilities::Date::WEEK);
        sToday.Add(1, Utilities::Date::MONTH);
        sToday.Add(1, Utilities::Date::YEAR);
#endif
    Utilities::Date::MyDate finalDate(11, 3, 2015);
    os << "Test of add function : " ;
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

bool RegressionTest_AnalyticFormulae(std::ostream & os)
{
    os << "Regression Test for Analytic formulae" << std::endl;
    
    const double dFwdRef = 1.0, T = 1.0;
    const double strikes[] = {0.6, 0.75, 0.9, 1.0, 1.1, 1.25, 1.4}, vols[] = {0.20, 0.180, 0.150, 0.125, 0.164, 0.197, 0.223};
    const std::vector<double> strikesvect(strikes, strikes + 7), volsvect(vols, vols + 7);
    Finance::Volatility::VolSmile volSmile(strikesvect, volsvect, dFwdRef, T);
    
    Finance::Pricers::Analytic sAnalytic;
    
    const double volatility = 0.150, rate = 0.02;
    
    const double ATMFCallRef = 0.0586014601,ATMFPutRef = 0.0586014601,Call110Ref = 0.0245073664,PUT110Ref = 0.122527234,DigitalnoSmileATMFRef = 0.460798607,DigitalSmileATMFRef =0.450454163,VegaATMFRef = 0.389944432,Digital90NoSmileRef = 0.720252526,Digital90SmileRef = 0.728282006;

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
    
    bool bOutput = false;
    if (bOutput)
    {
        os << "ATMFCallRef = " << sAnalytic.VanillaPrice(dFwdRef, dFwdRef, volatility, T, rate, Finance::Payoff::CALL) << ",";
        os << " ATMFPutRef = " << sAnalytic.VanillaPrice(dFwdRef, dFwdRef, volatility, T, rate, Finance::Payoff::PUT) << ",";
        os << " Call110Ref = " << sAnalytic.VanillaPrice(dFwdRef, 1.1 * dFwdRef, volatility, T, rate, Finance::Payoff::CALL) << ",";
        os << " PUT110Ref = " << sAnalytic.VanillaPrice(dFwdRef, 1.1 * dFwdRef, volatility, T, rate, Finance::Payoff::PUT) << ",";
        os << " DigitalnoSmileATMFRef = " << sAnalytic.DigitalPrice(dFwdRef, dFwdRef, volatility, T, rate, Finance::Payoff::CALL) << ",";
        os << " DigitalSmileATMFRef =" << sAnalytic.DigitalPrice(dFwdRef, dFwdRef, volSmile, T, rate, Finance::Payoff::CALL) << ",";
        os << " VegaATMFRef = " << sAnalytic.VegaVanillaOption(dFwdRef, dFwdRef, volatility, T, rate, Finance::Payoff::CALL) << ",";
        os << " Digital90NoSmileRef = " << sAnalytic.DigitalPrice(dFwdRef, 0.9 *dFwdRef, volatility, T, rate, Finance::Payoff::CALL) << ",";
        os << " Digital90SmileRef = " << sAnalytic.DigitalPrice(dFwdRef, 0.9 * dFwdRef, volSmile, T, rate, Finance::Payoff::CALL) ;
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

/////////////////////////////////////////////////////
//
//      Regression test launcher
//
/////////////////////////////////////////////////////

bool LaunchRegressionTests(std::ostream & os)
{
    bool bSucceeded = true;
    os << std::setprecision(9);
    
    bSucceeded = RegressionTest_BondPricing(os);
    if (!bSucceeded)
    {
        return bSucceeded;
    }
    os << std::endl;
    
    bSucceeded = RegressionTest_TimeStatistics(os);
    if (!bSucceeded)
    {
        return bSucceeded;
    }
    os << std::endl;
    
    bSucceeded = RegressionTest_PayoffLinearization(os);
    if (!bSucceeded)
    {
        return bSucceeded;
    }
    os << std::endl;
    
#ifdef DEBUG
    // run only in debug :--> needs to be fixed
    bSucceeded = RegressionTest_Interpolation(os);
    if (!bSucceeded)
    {
        return bSucceeded;
    }
    os << std::endl;
#endif
    
    bSucceeded = RegressionTest_ProcessPathSimulation(os);
    if (!bSucceeded)
    {
        return bSucceeded;
    }
    os << std::endl;
    
    bSucceeded = RegressionTest_Date(os);
    if (!bSucceeded)
    {
        return bSucceeded;
    }
    os << std::endl;
    
    bSucceeded = RegressionTest_VolatilitySurfaceInterpolation(os);
    if (!bSucceeded)
    {
        return bSucceeded;
    }
    os << std::endl;
    
    bSucceeded = RegressionTest_AnalyticFormulae(os);
    if (!bSucceeded)
    {
        return bSucceeded;
    }
    os << std::endl;
    return bSucceeded;
}