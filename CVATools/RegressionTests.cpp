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
#include "StatisticGatherer.h"
#include "muParser.h"
#include "PayoffParser.h"
#include "GaussianKernel.h"

#include "Printcpp.h"
#include "MargrabeOptionVasicek.h"

#include "Player.h"
#include "Tournament.h"
#include "GreaterScoreSorter.h"
#include "DummyRandomSimulator.h"

//  Declaration of all the regression tests

RegressionTest::RegressionTest(std::ostream & os) : m_out(os)
{}

bool RegressionTest::BondPricing() const
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
        
        m_out << "Test Bond Price : ";

        if (fabs(dBondPrice - dRefBondPrice) < dTolerance)
        {
            m_out << "SUCCEEDED" << std::endl;
        }
        else
        {
            m_out << "FAILED" << std::endl;
            return false;
        }
        
        m_out << "Test Bond Yield : ";
        const double dPriceToYield = sBondPricer.PriceToYield(dBondPrice);
        const double dRefYield = 0.0272162086597243;
        if (fabs(dPriceToYield - dRefYield) < dTolerance)
        {
            m_out << "SUCCEEDED" << std::endl;
        }
        else
        {
            m_out << "FAILED" << std::endl;
            return false;
        }
        
        m_out << "Test Bond I-Spread : ";
        const double dISpread = sBondPricer.I_Spread(dBondPrice);
        const double dRefISpread =-0.000364158958578442;
        if (fabs(dISpread - dRefISpread) < dTolerance)
        {
            m_out << "SUCCEEDED" << std::endl;
        }
        else
        {
            m_out << "FAILED" << std::endl;
            return false;
        }
        
        m_out << "Test Bond Z-Spread : ";
        const double dZSpread = sBondPricer.Z_Spread(dBondPrice);	
        const double dRefZSpread = 0.000384933028693842;
        if (fabs(dZSpread - dRefZSpread) < dTolerance)
        {
            m_out << "SUCCEEDED" << std::endl;
        }
        else
        {
            m_out << "FAILED" << std::endl;
            return false;
        }
    }
    catch(const Utilities::MyException & e)
    {
        m_out << "MyException caught : " << std::endl;
        m_out << e.what() << std::endl;
        return false;
    }
    catch(const std::exception & e)
    {
        m_out << "Exception caught : " << std::endl;
        m_out << e.what() << std::endl;
        return false;
    }
    catch(...)
    {
        m_out << "Unknown exception caught" << std::endl;
        return false;
    }
    return true;
}

bool RegressionTest::TimeStatistics() const
{
    try
    {
        // Regression Test Statistics Time
        std::size_t iNTimes = 10;
        m_out << std::endl;
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
        m_out << "Mean old time elapsed  " << dTimeOld / iNTimes << " seconds" << std::endl;
        m_out << "Mean time elapsed  " << dTimeNew / iNTimes << " seconds" << std::endl;
        
        m_out << "Time ratio : " << dTimeNew / dTimeOld << std::endl;
        m_out << "Computation mean : ";
        if (dTimeNew < 1.25 * dTimeOld)
        {
            m_out << "SUCCEEDED" << std::endl;
        }
        else
        {
            m_out << "FAILED" << std::endl;
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
        m_out << "Variance old time elapsed  " << dTimeOld / iNTimes << " seconds" << std::endl;
        m_out << "Variance time elapsed  " << dTimeNew / iNTimes << " seconds" << std::endl;
        
        m_out << "Time ratio : " << dTimeNew / dTimeOld << std::endl;
        m_out << "Computation variance : ";
        //  New algorithm seems to be around 3 times slower
        if (3.0 * dTimeNew > dTimeOld)
        {
            m_out << "SUCCEEDED" << std::endl;
        }
        else
        {
            m_out << "FAILED" << std::endl;
            return false;
        }
    }
    catch (const Utilities::MyException & excep)
    {
        m_out << "MyException caught : " << excep.what() << std::endl;
        return false;
    }
    catch (const std::exception & excep)
    {
        m_out << "std::exception caught : " << excep.what() << std::endl;
        return false;
    }
    catch (...)
    {
        m_out << "Unknown exception caught" << std::endl;
        return false;
    }
    return true;
}

bool RegressionTest::PayoffLinearization() const
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
    m_out << "Payoff linearization : " ;
    if (fabs(dRegCoefs.first - dRefCoefStock) < dEpsilon && fabs(dRegCoefs.second - dRefConstant) < dEpsilon)
    {
        m_out << "SUCCEDEED" << std::endl;
    }
    else
    {
        m_out << "FAILED" << std::endl;
        return false;
    }
    
    return true;
}

bool RegressionTest::Interpolation() const
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
    m_out << "Linear interpolation : ";
    if (dErrorlin < dTolerance)
    {
        m_out << "SUCCEEDED" << std::endl;
    }
    else
    {
        m_out << "FAILED" << std::endl;
        return false;
    }
    m_out << "Log-lin DF interpolation : ";
    if (dErrorloglindf < dTolerance)
    {
        m_out << "SUCCEEDED" << std::endl;
    }
    else
    {
        m_out << "FAILED" << std::endl;
        return false;
    }
    m_out << "Left continuous interpolation : ";
    if (dErrorleftcontinuous < dTolerance)
    {
        m_out << "SUCCEEDED" << std::endl;
    }
    else
    {
        m_out << "FAILED" << std::endl;
        return false;
    }
    m_out << "Right continuous interpolation : ";
    if (dErrorrightcontinuous < dTolerance)
    {
        m_out << "SUCCEEDED" << std::endl;
    }
    else
    {
        m_out << "FAILED" << std::endl;
        return false;
    }
    m_out << "Hermite spline cubic interpolation  : ";
    if (dErrorhermite < dTolerance)
    {
        m_out << "SUCCEEDED" << std::endl;
    }
    else
    {
        m_out << "FAILED" << std::endl;
        return false;
    }
    m_out << "Hermite degree 5 interpolation  : ";
    if (dErrorhermite5 < dTolerance)
    {
        m_out << "SUCCEEDED" << std::endl;
    }
    else
    {
        m_out << "FAILED" << std::endl;
        return false;
    }
    return true;
}

bool RegressionTest::VolatilitySurfaceInterpolation() const
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
        m_out << excep.what() << std::endl;
        return false;
    }
    catch (const std::exception & excep)
    {
        m_out << excep.what() << std::endl;
        return false;
    }
    catch (...)
    {
        m_out << "Unknown exception caught" << std::endl;
        return false;
    }
    
    m_out << "Non-Arbitrageability of smile : " << volSmile.IsArbitrageFree() << std::endl;
    m_out << "SVI Parametrisation arbitrable ? " << sviParameterSolver.IsArbitrable(T) << std::endl;

    
    double dVolHermiteInterp[] = {0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.199955909,0.199689734,0.199081336,0.198094904,0.196754089,0.19512155,0.193282206,0.191329615,0.189354987,0.187438405,0.185641902,0.184004098,0.182536136,0.181218712,0.18,0.177819828,0.175742583,0.173828076,0.172080715,0.170466648,0.168928276,0.167396491,0.165800937,0.164078559,0.162180664,0.160078705,0.15776894,0.155276176,0.152656598,0.15,0.14717476,0.14340999,0.138521685,0.132949327,0.127473701,0.122974304,0.120221805,0.119701462,0.121463895,0.125,0.129374691,0.134125924,0.138991353,0.143745486,0.148209001,0.152256557,0.15582327,0.158909988,0.161587532,0.164,0.166327361,0.168636065,0.170945902,0.173265008,0.175592626,0.177921568,0.180240405,0.1825354,0.18479223,0.186997494,0.189140045,0.191212151,0.193210507,0.195137106,0.197,0.198859901,0.200861613,0.203076471,0.205502719,0.208085317,0.210733763,0.21333809,0.215783199,0.217961653,0.21978509,0.221194336,0.222168368,0.222732195,0.22296377,0.223,0.223,0.223,0.223,0.223,0.223,0.223,0.223,0.223,0.223};
    double dSVIParametrisationParabola[] = {0.246217359906585,0.241945342740466,0.237741155076599,0.233604978334171,0.229537201918785,0.225538420927118,0.221609434141311,0.21775124215424,0.213965045459236,0.210252242328285,0.206614426291565,0.20305338301888,0.19957108639063,0.196169693533214,0.192851538581995,0.189619124925319,0.186475115676871,0.183422322122295,0.180463689891393,0.177602282621018,0.174841262898164,0.172183870309549,0.169633396475047,0.16719315700901,0.164866460436744,0.162656574192893,0.160566687943254,0.158599874598679,0.156759049525174,0.155046928591975,0.153465985831816,0.152018411605961,0.150706072261238,0.149530472327733,0.148492720325275,0.14759349921766,0.146833042471939,0.146211116545954,0.145727010444791,0.145379532764281,0.145167016389154,0.145087330749816,0.14513790128119,0.145315735485671,0.145617454794485,0.146039331258876,0.146577327992045,0.147227142227616,0.147984249859302,0.148843950374371,0.149801411182459,0.150851710461506,0.151989877783612,0.15321093193507,0.154509915497553,0.155881925903665,0.157322142813912,0.158825851779613,0.16038846425512,0.162005534102156,0.163672770789663,0.165386049535555,0.167141418664223,0.168935104467731,0.170763513861793,0.172623235122085,0.174511036974356,0.176423866295079,0.178358844659588,0.180313263953108,0.182284581237916,0.184270413047822,0.186268529259853,0.188276846672943,0.190293422404702,0.192316447200316,0.194344238732189,0.1963752349552,0.198407987570317,0.200441155638684,0.20247349937908,0.204503874173783,0.206531224801055,0.208554579906853,0.21057304672352,0.212585806039323,0.214592107419391,0.216591264676037,0.218582651584289,0.220565697836828,0.222539885231257,0.224504744081668,0.226459849845796,0.228404819958608,0.230339310862888,0.232263015227272,0.234175659342196,0.236077000684323,0.23796682564018,0.239844947380012};
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
    m_out << "Hermite Interpolation of smile : ";
    if (dErrorInterpHermite < dTolerance)
    {
        m_out << "SUCCEEDED" << std::endl;
    }
    else
    {
        m_out << "FAILED" << std::endl;
        return false;
    }
    m_out << "SVI Parametrisation of smile : " ;
    if (dErrorSVIParabola < dTolerance)
    {
        m_out << "SUCCEEDED" << std::endl;
    }
    else
    {
        m_out << "FAILED. Error = " << dErrorSVIParabola << std::endl;
        return false;
    }
    m_out << "Smile skew : " ;
    if (dErrorSmileSkew < dTolerance)
    {
        m_out << "SUCCEEDED" << std::endl;
    }
    else
    {
        m_out << "FAILED" << std::endl;
        return false;
    }
    m_out << "Convexity of smile : " ;
    if (dErrorSmileConvexity < dTolerance)
    {
        m_out << "SUCCEEDED" << std::endl;
    }
    else
    {
        m_out << "FAILED" << std::endl;
        return false;
    }
    return true;
}

bool RegressionTest::ProcessPathSimulation() const
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
    
    m_out << "Square Root process Simulation : ";
    if (dDiffSquareRoot < dTolerance)
    {
        m_out << "SUCCEEDED" << std::endl;
    }
    else
    {
        m_out << "FAILED" << std::endl;
        return false;
    }
    m_out << "Ornstein Ulhenbeck process Simulation : ";
    if (dDiffOU < dTolerance)
    {
        m_out << "SUCCEEDED" << std::endl;
    }
    else
    {
        m_out << "FAILED" << std::endl;
        return false;
    }
    m_out << "Black Scholes process Simulation : ";
    if (dDiffBS < dTolerance)
    {
        m_out << "SUCCEEDED" << std::endl;
    }
    else
    {
        m_out << "FAILED" << std::endl;
        return false;
    }
    m_out << "Stochastic correlation process Simulation : ";
    if (dDiffSC < dTolerance)
    {
        m_out << "SUCCEEDED" << std::endl;
    }
    else
    {
        m_out << "FAILED" << std::endl;
        return false;
    }
    m_out << "CEV process Simulation : ";
    if (dDiffCEV < dTolerance)
    {
        m_out << "SUCCEEDED" << std::endl;
    }
    else
    {
        m_out << "FAILED" << std::endl;
        return false;
    }
    return true;
}

//  Regression test for date
bool RegressionTest::Date() const
{
    Utilities::Date::MyDate sToday(3,2,2014);
    
    m_out << "Today is " << sToday << std::endl;
    sToday = sToday.Add(1, Utilities::Date::DAY);
    sToday = sToday.Add(1, Utilities::Date::WEEK);
    sToday = sToday.Add(1, Utilities::Date::MONTH);
    sToday = sToday.Add(1, Utilities::Date::YEAR);
    sToday = sToday.Add(1, Utilities::Date::BUSINESSDAY);
    Utilities::Date::MyDate finalDate(12, 3, 2015);
    if (sToday == finalDate)
    {
        m_out << "SUCCEEDED" << std::endl;
    }
    else
    {
        m_out << "FAILED" << std::endl;
        return false;
    }
    Utilities::Date::MyTenor tenor(2,Utilities::Date::DAY);
    sToday = sToday.Add(tenor);
    Utilities::Date::MyDate date(14,3,2015);
    if (sToday == date)
    {
        m_out << "SUCCEEDED" << std::endl;
    }
    else
    {
        m_out << "FAILED" << std::endl;
        return false;
    }
    return true;
}

bool RegressionTest::AnalyticFormulae() const
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
    
#ifdef _DEBUG
    {
        m_out << std::setprecision(9);
        m_out << "ATMFCallRef = " << sAnalytic.VanillaPrice(dFwdRef, dFwdRef, volatility, T, rate, Finance::Payoff::CALL) << ",";
        m_out << " ATMFPutRef = " << sAnalytic.VanillaPrice(dFwdRef, dFwdRef, volatility, T, rate, Finance::Payoff::PUT) << ",";
        m_out << " Call110Ref = " << sAnalytic.VanillaPrice(dFwdRef, 1.1 * dFwdRef, volatility, T, rate, Finance::Payoff::CALL) << ",";
        m_out << " PUT110Ref = " << sAnalytic.VanillaPrice(dFwdRef, 1.1 * dFwdRef, volatility, T, rate, Finance::Payoff::PUT) << ",";
        m_out << " DigitalnoSmileATMFRef = " << sAnalytic.DigitalPrice(dFwdRef, dFwdRef, volatility, T, rate, Finance::Payoff::CALL) << ",";
        m_out << " DigitalSmileATMFRef =" << sAnalytic.DigitalPrice(dFwdRef, dFwdRef, volSmile, T, rate, Finance::Payoff::CALL) << ",";
        m_out << " VegaATMFRef = " << sAnalytic.VegaVanillaOption(dFwdRef, dFwdRef, volatility, T, rate, Finance::Payoff::CALL) << ",";
        m_out << " Digital90NoSmileRef = " << sAnalytic.DigitalPrice(dFwdRef, 0.9 *dFwdRef, volatility, T, rate, Finance::Payoff::CALL) << ",";
        m_out << " Digital90SmileRef = " << sAnalytic.DigitalPrice(dFwdRef, 0.9 * dFwdRef, volSmile, T, rate, Finance::Payoff::CALL) ;
        m_out << " Asian option = " << sAnalytic.AsianOption(spot, dFwdRef, Finance::Payoff::CALL, volatility, T, rate, observationTimesvect, pastFixings) << std::endl;
        m_out << ";" << std::endl;
    }
#endif
    
    const double tolerance = 1e-06;
   
    if (error < tolerance)
    {
        m_out << "SUCCEEDED" << std::endl;
    }
    else
    {
        m_out << "FAILED" << std::endl;
        return false;
    }
    return true;
}

bool RegressionTest::MatrixInversion() const
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
    m_out << inverse;
    m_out << refinvmatrix;
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
        m_out << "SUCCEEDED" << std::endl;
    }
    else
    {
        m_out << "FAILED" << std::endl;
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

bool RegressionTest::NewtonSolver() const
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
        m_out << "SUCCEEDED" << std::endl;
    }
    else
    {
        m_out << "FAILED";
        return false;
    }
    return true;
}

bool RegressionTest::Ticker() const
{
    Utilities::Ticker<double> tick("tickdouble");
    
    tick.Store(10.0);
    double res = tick.Instance();
    std::string name = tick.Name();
    const double tolerance = 1e-10;
    if (name == "tickdouble.1" && std::abs(res - 10.0) < tolerance)
    {
        m_out << "SUCCEEDED" << std::endl;
        return true;
    }
    else
    {
        m_out << "FAILED" << std::endl;
        return false;
    }
}

bool RegressionTest::Sobol() const
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
        m_out << "SUCCEEDED" << std::endl;
        return true;
    }
    else
    {
        m_out << "FAILED" << std::endl;
        return false;
    }
}

bool RegressionTest::DebyeFunction() const
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
        m_out << "SUCCEEDED" << std::endl;
        return true;
    }
    else
    {
        m_out << "FAILED" << std::endl;
        return false;
    }
}

bool RegressionTest::Statistic() const
{
    std::vector<std::tr1::shared_ptr<Maths::StatisticGatherer> > vect;
    vect.push_back(std::tr1::shared_ptr<Maths::StatisticGatherer>(new Maths::Statistic<Maths::MEAN>));
    vect.push_back(std::tr1::shared_ptr<Maths::StatisticGatherer>(new Maths::Statistic<Maths::STANDARD_DEVIATION>));
    vect.push_back(std::tr1::shared_ptr<Maths::StatisticGatherer>(new Maths::Moment<3>));
    vect.push_back(std::tr1::shared_ptr<Maths::StatisticGatherer>(new Maths::Statistic<Maths::MIN>));
    vect.push_back(std::tr1::shared_ptr<Maths::StatisticGatherer>(new Maths::Statistic<Maths::MAX>));
    
    double refvalues[] = {9.75,33.3125,1901.25,0,19.5};
    const double tolerance = 1e-10;
    
    for (size_t i = 0 ; i < vect.size() ; ++i)
    {
        for (double x = 0 ; x < 20 ; x += 0.5)
        {
            vect[i]->DumpOneResult(x);
        }
        
        if (std::abs(vect[i]->GetResultsSoFar()-refvalues[i]) > tolerance)
        {
            m_out << std::setprecision(15) << "Results : " << vect[i]->GetResultsSoFar() << std::endl;
            m_out << std::setprecision(15) << "RefValues : " << refvalues[i] << std::endl;
            m_out << "FAILED" << std::endl;
            return false;
        }
    }
    
    m_out << "SUCCEEDED" << std::endl;
    return true;
}

namespace {
    // Function callback
    double MySqr(double a_fVal)
    {
        return a_fVal*a_fVal;
    }
}

bool RegressionTest::muParser() const
{
    // Example suggested in http://muparser.beltoforion.de/mup_example.html#idExample
    try
    {
        double fVal = 1;
        mu::Parser p;
        p.DefineVar("A", &fVal);
        p.DefineFun("MYSQR", MySqr);
        p.SetExpr("MYSQR(a)*_pi+min(10,a)");
        
        const double refValues[] = {0,4.14159265358979,14.5663706143592,31.2743338823081,54.2654824574367,83.5398163397448,119.097335529233,160.9380400259,209.061929829747,263.469004940773,324.159265358979,390.132711084365,462.38934211693,540.929158456675,625.752160103599,716.858347057703,814.247719318987,917.92027688745,1027.87601976309,1144.11494794592,1266.63706143592,1395.4423602331,1530.53084433746,1671.902513749,1819.55736846772,1973.49540849362,2133.7166338267,2300.22104446696,2473.0086404144,2652.07942166902,2837.43338823081,3029.07054009979,3226.99087727595,3431.19439975928,3641.6811075498,3858.4510006475,4081.50407905237,4310.84034276443,4546.45979178366,4788.36242611007,5036.54824574367,5291.01725068444,5551.76944093239,5818.80481648753,6092.12337734984,6371.72512351933,6657.610054996,6949.77817177985,7248.22947387088,7552.96396126909,7863.98163397448,8181.28249198705,8504.8665353068,8834.73376393373,9170.88417786784,9513.31777710913,9862.03456165759,10217.0345315132,10578.3176866761,10945.8840271461,11319.7335529233,11699.8662640076,12086.2821603992,12478.9812420979,12877.9635091038,13283.2289614169,13694.7775990371,14112.6094219646,14536.7244301992,14967.122623741,15403.80400259,15846.7685667461,16296.0163162095,16751.54725098,17213.3613710577,17681.4586764426,18155.8391671346,18636.5028431339,19123.4497044403,19616.6797510539,20116.1929829747,20621.9894002026,21134.0690027378,21652.4317905801,22177.0777637296,22708.0069221863,23245.2192659501,23788.7147950211,24338.4935093994,24894.5554090848,25456.9004940773,26025.5287643771,26600.440219984,27181.6348608981,27769.1126871194,28362.8736986479,28962.9178954835,29569.2452776264,30181.8558450764,30800.7495978336};
        
        const double tolerance = 1e-8;
        double error = 0.0;
        
        for (std::size_t a=0; a<100; ++a)
        {
            fVal = a;  // Change value of variable a
            error += std::abs(p.Eval()-refValues[a]);
        }
        
        if (error > tolerance)
        {
            m_out << "muParser error " << error << " is above tolerance " << tolerance << std::endl;
            return false;
        }
    }
    catch (const std::exception &e)
    {
        m_out << "muParser failed with error : " << e.what() << std::endl;
        return false;
    }
    m_out << "SUCCEEDED" << std::endl;
    return true;
}

bool RegressionTest::MyException() const
{
    int line = 0;
    try
    {
        line = __LINE__ + 1;
        throw EXCEPTION("Dummy Exception");
    }
    catch (const Utilities::MyException & e)
    {
        std::stringstream ss;
        ss << "Dummy Exception in function : MyException (line " << line << ") in RegressionTests.cpp";
        const std::string message = ss.str();
        if (strcmp(e.what(), message.c_str())!=0)
        {
            m_out << "My Exception failed : messages are not the same" << std::endl;
            m_out << "Message : " << message.c_str() << std::endl;
            m_out << "Exception message : " << e.what() << std::endl;
            return false;
        }
        else
        {
            m_out << "SUCCEEDED" << std::endl;
            return true;
        }
    }
}

bool RegressionTest::PayoffParser() const
{
    try
    {
        Finance::Payoff::PayoffParser payoff1 ("max(s-1,0)"), payoff2("MAX(S-1,0)");
        
        const double tolerance = 1e-14;
        for (double x = 0 ; x < 10 ; ++x)
        {
            if (std::abs(payoff1(x)-payoff2(x)) > tolerance)
            {
                std::stringstream ss;
                ss << std::setprecision(15) <<"Not the same payoff. Payoff1 : " << payoff1(x) << " / Payoff 2 : " << payoff2(x) << std::endl;
                throw EXCEPTION("Not the same payoff");
            }
        }
    }
    catch (const std::exception & e)
    {
        m_out << "std::exception caught : " << e.what() << std::endl;
        return false;
    }
    m_out << "SUCCEEDED" << std::endl;
    return true;
}

namespace DefaultArgs{
    class A
    {
    public:
        virtual int f(const int i = 1) const
        {
            return i;
        }
    };
    
    class B : public A
    {
    public:
        int f(const int i) const
        {
            return i;
        }
    };
}

bool RegressionTest::DefaultArguments() const
{
    std::tr1::shared_ptr<DefaultArgs::A> a(new DefaultArgs::B);
    int result = a->f();

    if (std::abs(result - 1) < 1)
    {
        m_out << "SUCCEEDED" << std::endl;
        return true;
    }
    else
    {
        m_out << "FAILED" << std::endl;
        return false;
    }
}

bool RegressionTest::GaussianKernel() const
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
        
        double refValues[] = {1.92874984796392e-22,5.24288566336353e-22,1.42516408274095e-21,3.87399762868721e-21,1.05306173575538e-20,2.86251858054943e-20,7.78113224113391e-20,2.1151310375911e-19,5.7495222642936e-19,1.562882189335e-18,4.24835425529159e-18,1.15482241730157e-17,3.13913279204805e-17,8.53304762574413e-17,2.31952283024358e-16,6.30511676014698e-16,1.71390843154203e-15,4.65888614510341e-15,1.2664165549094e-14,3.44247710846986e-14,9.35762296883937e-14,2.54366564737631e-13,6.91440010693549e-13,1.87952881653557e-12,5.10908902803727e-12,1.38879438647712e-11,3.7751345441366e-11,1.02618796306489e-10,2.78946809209083e-10,7.58256042216242e-10,2.06115361819022e-09,5.60279640614598e-09,1.52299795127605e-08,4.13993754739436e-08,1.12535162055096e-07,3.05902226925628e-07,8.31528027664145e-07,2.26032429790361e-06,6.1441746022148e-06,1.67014218480954e-05,4.53978687024352e-05,0.000123394575986234,0.000335350130466484,0.00091105119440066,0.00247262315663483,0.00669285092428497,0.017986209962092,0.0474258731775677,0.11920292202212,0.268941421369999,0.500000000000005,0.731058578630009,0.880797077977885,0.952574126822434,0.982013790037909,0.993307149075715,0.997527376843365,0.999088948805599,0.999664649869534,0.999876605424014,0.999954602131298,0.999983298578152,0.999993855825398,0.999997739675702,0.999999168471972,0.999999694097773,0.999999887464838,0.999999958600625,0.99999998477002,0.999999994397204,0.999999997938846,0.999999999241744,0.999999999721053,0.999999999897381,0.999999999962249,0.999999999986112,0.999999999994891,0.99999999999812,0.999999999999309,0.999999999999746,0.999999999999907,0.999999999999966,0.999999999999987,0.999999999999995,0.999999999999998,0.999999999999999,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1.00000000000001,1.00000000000003,1.00000000000009,1.00000000000025,1.00000000000069,1.00000000000188,1.00000000000511,1.00000000001389,1.00000000003775,1.00000000010262,1.00000000027895,1.00000000075826,1.00000000206115,1.0000000056028,1.00000001522998,1.00000004139938,1.00000011253516,1.00000030590223,1.00000083152803,1.0000022603243,1.0000061441746,1.00001670142185,1.0000453978687,1.00012339457599,1.00033535013047,1.0009110511944,1.00247262315663,1.00669285092429,1.01798620996209,1.04742587317757,1.11920292202213,1.26894142137002,1.50000000000003,1.73105857863003,1.88079707797789,1.95257412682244,1.98201379003791,1.99330714907572,1.99752737684337,1.9990889488056,1.99966464986953,1.99987660542401,1.9999546021313,1.99998329857815,1.9999938558254,1.9999977396757,1.99999916847197,1.99999969409777,1.99999988746484,1.99999995860062,1.99999998477002,1.9999999943972,1.99999999793885,1.99999999924174,1.99999999972105,1.99999999989738,1.99999999996225,1.99999999998611,1.99999999999489,1.99999999999812,1.99999999999931,1.99999999999975,1.99999999999991,1.99999999999997,1.99999999999999,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2.00000000000001,2.00000000000003,2.00000000000009,2.00000000000025,2.00000000000069,2.00000000000188,2.00000000000511,2.00000000001389,2.00000000003775,2.00000000010262,2.00000000027895,2.00000000075826,2.00000000206115,2.0000000056028,2.00000001522998,2.00000004139938,2.00000011253516,2.00000030590223,2.00000083152803,2.0000022603243,2.0000061441746,2.00001670142185,2.0000453978687,2.00012339457599,2.00033535013047,2.0009110511944,2.00247262315663,2.00669285092428,2.01798620996208,2.04742587317753,2.11920292202202,2.26894142136982,2.49999999999977,2.73105857862982,2.88079707797778,2.95257412682239,2.98201379003789,2.99330714907571,2.99752737684336,2.9990889488056,2.99966464986953,2.99987660542401,2.9999546021313,2.99998329857815,2.9999938558254,2.9999977396757,2.99999916847197,2.99999969409777,2.99999988746484,2.99999995860062,2.99999998477002,2.9999999943972,2.99999999793885,2.99999999924174,2.99999999972105,2.99999999989738,2.99999999996225,2.99999999998611,2.99999999999489,2.99999999999812,2.99999999999931,2.99999999999975,2.99999999999991,2.99999999999997,2.99999999999999,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3.00000000000001,3.00000000000003,3.00000000000009,3.00000000000025,3.00000000000069,3.00000000000188,3.00000000000511,3.00000000001389,3.00000000003775,3.00000000010262,3.00000000027895,3.00000000075826,3.00000000206115,3.0000000056028,3.00000001522998,3.00000004139938,3.00000011253516,3.00000030590223,3.00000083152803,3.0000022603243,3.0000061441746,3.00001670142185,3.0000453978687,3.00012339457599,3.00033535013047,3.0009110511944,3.00247262315663,3.00669285092427,3.01798620996204,3.04742587317743,3.1192029220218,3.2689414213694,3.49999999999923,3.7310585786294,3.88079707797756,3.95257412682229,3.98201379003785,3.99330714907569,3.99752737684336,3.9990889488056,3.99966464986953,3.99987660542401,3.9999546021313,3.99998329857815,3.9999938558254,3.9999977396757,3.99999916847197,3.99999969409777,3.99999988746484,3.99999995860062,3.99999998477002,3.9999999943972,3.99999999793885,3.99999999924174,3.99999999972105,3.99999999989738,3.99999999996225,3.99999999998611,3.99999999999489,3.99999999999812,3.99999999999931,3.99999999999975,3.99999999999991,3.99999999999997,3.99999999999999,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4.00000000000001,4.00000000000003,4.00000000000009,4.00000000000025,4.00000000000069,4.00000000000188,4.00000000000511,4.00000000001389,4.00000000003775,4.00000000010262,4.00000000027895,4.00000000075826,4.00000000206115,4.0000000056028,4.00000001522998,4.00000004139938,4.00000011253516,4.00000030590223,4.00000083152803,4.0000022603243,4.0000061441746,4.00001670142185,4.0000453978687,4.00012339457599,4.00033535013046,4.0009110511944,4.00247262315662,4.00669285092425,4.017986209962,4.04742587317734,4.11920292202158,4.26894142136899,4.49999999999871,4.73105857862899,4.88079707797734,4.9525741268222,4.98201379003782,4.99330714907568,4.99752737684335,4.99908894880559,4.99966464986953,4.99987660542401,4.9999546021313,4.99998329857815,4.9999938558254,4.9999977396757,4.99999916847197,4.99999969409777,4.99999988746484,4.99999995860062,4.99999998477002,4.9999999943972,4.99999999793885,4.99999999924174,4.99999999972105,4.99999999989738,4.99999999996225,4.99999999998611,4.99999999999489,4.99999999999812,4.99999999999931,4.99999999999975,4.99999999999991,4.99999999999997,4.99999999999999,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5.00000000000001,5.00000000000003,5.00000000000009,5.00000000000025,5.00000000000069,5.00000000000188,5.00000000000511,5.00000000001389,5.00000000003775,5.00000000010262,5.00000000027895,5.00000000075826,5.00000000206115,5.0000000056028,5.00000001522998,5.00000004139938,5.00000011253516,5.00000030590223,5.00000083152803,5.0000022603243,5.0000061441746,5.00001670142185,5.0000453978687,5.00012339457599,5.00033535013046,5.00091105119439,5.00247262315662,5.00669285092424,5.01798620996196,5.04742587317724,5.11920292202136,5.26894142136857,5.49999999999818,5.73105857862857,5.88079707797711,5.9525741268221,5.98201379003778,5.99330714907567,5.99752737684335,5.99908894880559,5.99966464986953,5.99987660542401,5.9999546021313,5.99998329857815,5.9999938558254,5.9999977396757,5.99999916847197,5.99999969409777,5.99999988746484,5.99999995860062,5.99999998477002,5.9999999943972,5.99999999793885,5.99999999924174,5.99999999972105,5.99999999989738,5.99999999996225,5.99999999998611,5.99999999999489,5.99999999999812,5.99999999999931,5.99999999999975,5.99999999999991,5.99999999999997,5.99999999999999,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6.00000000000001,6.00000000000003,6.00000000000009,6.00000000000025,6.00000000000069,6.00000000000188,6.00000000000511,6.00000000001389,6.00000000003775,6.00000000010262,6.00000000027895,6.00000000075826,6.00000000206115,6.0000000056028,6.00000001522998,6.00000004139938,6.00000011253516,6.00000030590223,6.00000083152803,6.0000022603243,6.0000061441746,6.00001670142185,6.0000453978687,6.00012339457598,6.00033535013046,6.00091105119439,6.00247262315661,6.00669285092422,6.01798620996193,6.04742587317714,6.11920292202113,6.26894142136815,6.49999999999765,6.73105857862815,6.88079707797689,6.952574126822,6.98201379003774,6.99330714907565,6.99752737684334,6.99908894880559,6.99966464986953,6.99987660542401,6.9999546021313,6.99998329857815,6.9999938558254,6.9999977396757,6.99999916847197,6.99999969409777,6.99999988746484,6.99999995860062,6.99999998477002,6.9999999943972,6.99999999793885,6.99999999924174,6.99999999972105,6.99999999989738,6.99999999996225,6.99999999998611,6.99999999999489,6.99999999999812,6.99999999999931,6.99999999999975,6.99999999999991,6.99999999999996,6.99999999999999,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7.00000000000001,7.00000000000001,7.00000000000003,7.00000000000009,7.00000000000025,7.00000000000069,7.00000000000188,7.00000000000511,7.00000000001389,7.00000000003775,7.00000000010262,7.00000000027895,7.00000000075826,7.00000000206115,7.0000000056028,7.00000001522998,7.00000004139938,7.00000011253516,7.00000030590223,7.00000083152803,7.0000022603243,7.0000061441746,7.00001670142185,7.0000453978687,7.00012339457599,7.00033535013046,7.00091105119439,7.00247262315661,7.00669285092421,7.01798620996189,7.04742587317705,7.11920292202091,7.26894142136773,7.49999999999711,7.73105857862773,7.88079707797666,7.95257412682191,7.9820137900377,7.99330714907564,7.99752737684334,7.99908894880559,7.99966464986953,7.99987660542401,7.9999546021313,7.99998329857815,7.9999938558254,7.9999977396757,7.99999916847197,7.99999969409777,7.99999988746484,7.99999995860063,7.99999998477002,7.9999999943972,7.99999999793885,7.99999999924174,7.99999999972105,7.99999999989738,7.99999999996225,7.99999999998611,7.99999999999489,7.99999999999812,7.99999999999931,7.99999999999975,7.99999999999991,7.99999999999996,7.99999999999999,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8.00000000000001,8.00000000000001,8.00000000000003,8.00000000000009,8.00000000000025,8.00000000000069,8.00000000000188,8.00000000000511,8.00000000001389,8.00000000003775,8.00000000010262,8.00000000027895,8.00000000075826,8.00000000206115,8.0000000056028,8.00000001522998,8.00000004139938,8.00000011253516,8.00000030590223,8.00000083152803,8.0000022603243,8.0000061441746,8.00001670142185,8.0000453978687,8.00012339457598,8.00033535013046,8.00091105119439,8.0024726231566,8.00669285092419,8.01798620996185,8.04742587317695,8.11920292202069,8.26894142136731,8.49999999999658,8.73105857862731,8.88079707797644,8.95257412682181,8.98201379003767,8.99330714907562,8.99752737684333,8.99908894880559,8.99966464986953,8.99987660542401,8.9999546021313,8.99998329857815,8.9999938558254,8.9999977396757,8.99999916847197,8.99999969409777,8.99999988746484,8.99999995860062,8.99999998477002,8.9999999943972,8.99999999793885,8.99999999924174,8.99999999972105,8.99999999989738,8.99999999996225,8.99999999998611,8.99999999999489,8.99999999999812,8.99999999999931,8.99999999999975,8.99999999999991,8.99999999999997,8.99999999999999,8.99999999999999,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9};
        
        double error = 0;
        int i = 0;
        for (double x = 0 ; x < 9.5 ; x += 0.01, ++i)
        {
            const double result = sGaussianKernel.Estimate(dXY, x);
#ifdef _DEBUG
            m_out << x << ";" << result << std::endl;
#endif
            error += std::abs(refValues[i]-result);
        }
        
        const double tolerance = 1e-08;
        if (error > tolerance)
        {
            m_out << "FAILED" << std::endl;
            return false;
        }
    }
    catch (const std::exception & e)
    {
        m_out << "Error : " << e.what() << std::endl;
        return false;
    }
    m_out << "SUCCEEDED" << std::endl;
    return true;
}

bool RegressionTest::MargrabeOptionVasicek() const
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
    std::size_t iNDates = 2, iNPaths = 1;
    for (std::size_t i = 0 ; i < iNDates; ++i)
    {
        dDates.push_back(static_cast<double>(i) / (iNDates-1));
    }
    
    Utilities::SimulationDataMultiDim sData = sOption.simulate(dDates, iNPaths);
#ifdef _DEBUG
    m_out << "Printing of the simulated data " << std::endl;
    m_out << std::setprecision(15) << sData << std::endl;
#endif
    
    const double refValues[] = {4.60644557974016,
        4.68799906707437,
        0.0263054037476569,
        0.0309189871480756};
    
    double error = 0;
    const std::map<double, std::map<size_t, std::vector<double> > > & data = sData.GetData();
    std::map<double, std::map<size_t, std::vector<double> > >::const_iterator it = data.begin();
    ++it;
    
    std::map<size_t, std::vector<double> >::const_iterator it2 = it->second.find(0);
    
    for (size_t i = 0 ; i < 4 ; ++i)
    {
        error += std::abs(it2->second[i] - refValues[i]);
    }
    
    const double tolerance = 1e-08;
    if (error < tolerance)
    {
        m_out << "SUCCEEDED" << std::endl;
        return true;
    }
    else
    {
        m_out << "FAILED" << std::endl;
        return false;
    }
}

bool RegressionTest::PlayerResultTest() const
{
    PlayerResult result1("Tournament1", Utilities::Date::MyDate(30,9,2014), 30, 288, 1.5);
    
    if (result1.MissedCut())
    {
        m_out << "Missed Cut is true" << std::endl;
        return false;
    }
    
    if (result1.Position() != 30)
    {
        m_out << "Position is not 30" << std::endl;
        return false;
    }
    
    if (result1.Score() != 288)
    {
        m_out << "Score is not 288" << std::endl;
        return false;
    }
    
    if (result1.RankingPoints() != 1.5)
    {
        m_out << "Ranking points is not 1.5" << std::endl;
        return false;
    }
    m_out << "SUCCEEDED" << std::endl;
    return true;
}

bool RegressionTest::DummyTournament() const
{
    Tournament tournament("dummy",Utilities::Date::MyDate(18,12,2014));
    const size_t numPlayers = 100;
    std::vector<Player> players(numPlayers,std::string("")); // empty string is a char*
    for (size_t i = 0 ; i < numPlayers ; ++i)
    {
        std::stringstream ss;
        ss << "Player " << i;
        players[i] = Player(ss.str());
        
        tournament.AddPlayer(players[i]);
    }
    
    tournament.Simulate(DummyRandomSimulator(0));
    
    tournament.Rank(GreaterScoreSorter());
    
    size_t refValues[] = {2146335337,2139642574,2132723841,2116969294,2097549478,2091824407,2085187937,2064010129,2055540383,2042297871,2002830094,1950367213,1906706780,1846443803,1840335376,1830665860,1809249219,1797288065,1793547003,1791277536,1789614810,1779175845,1741849297,1734177661,1731106012,1719408956,1710028745,1671889999,1669187896,1664792818,1643550337,1579802159,1567674295,1566369460,1559526673,1514888112,1500357984,1462087311,1461728458,1370738826,1359072203,1294600846,1290446329,1269870926,1163120341,1152891831,1094100450,1073226880,1046126087,1040043610,1028169396,1009021007,1006609540,1002898451,968021766,926881476,899316322,897787792,892086236,890459872,838023412,822784415,819516268,810662187,809673979,792526220,764058775,763654014,679469414,675891343,664835076,631361083,608455363,590294128,569022154,525706991,520932930,515529753,496586426,480849991,428300259,422527594,400151788,393860762,309696691,250591794,247074805,210367714,205711490,158379552,145532761,115120654,77268269,68362598,66433441,57271926,52107318,28925691,27706653,19932546};
    Tournament::Players & tournamentPlayers = tournament.GetPlayers();
    
    size_t error = 0;
    for (size_t player = 0 ; player < tournamentPlayers.size() ; ++player)
    {
        error += fabs(tournamentPlayers[player].second.Score() - refValues[player]);
#ifdef _DEBUG
        m_out << players[player].first.Name() << ":" << players[player].second.Score() << std::endl;
#endif
    }
    
    if (error < 1)
    {
        m_out << "Score : SUCCEEDED" << std::endl;
    }
    else
    {
        m_out << "FAILED" << std::endl;
        return false;
    }
    
    size_t error2 = 0;
    for (size_t player = 0 ; player < players.size() ; ++player)
    {
        players[player].AddResult(tournament);
    }
    
    const size_t rank[] = {76,97,61,59,90,2,49,30,93,94,10,12,43,50,20,82,31,86,36,67,39,11,71,74,63,44,99,0,98,16,15,53,91,4,81,14,84,25,33,3,83,47,51,6,54,88,5,60,38,95,78,52,87,58,26,68,27,21,48,65,41,96,22,66,24,73,13,9,28,37,18,7,35,89,45,8,57,56,62,17,77,34,55,85,79,70,75,64,23,69,29,72,1,40,42,46,19,80,92,32};
    
    for (size_t player = 0 ; player < players.size() ; ++player)
    {
#ifdef _DEBUG
        m_out << players[player].Results()[0].Position() << ",";
#endif
        error2 += fabs(rank[player] - players[player].Results()[0].Position());
    }
    
    if (error2 < 1)
    {
        m_out << "Rank : SUCCEEDED" << std::endl;
        return true;
    }
    else
    {
        m_out << "FAILED" << std::endl;
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
    m_mapping.insert(std::make_pair("Statistic", &RegressionTest::Statistic));
    m_mapping.insert(std::make_pair("muParser", &RegressionTest::muParser));
    m_mapping.insert(std::make_pair("Exception", &RegressionTest::MyException));
    m_mapping.insert(std::make_pair("PayoffParser", &RegressionTest::PayoffParser));
    m_mapping.insert(std::make_pair("DefaultArguments", &RegressionTest::DefaultArguments));
    m_mapping.insert(std::make_pair("GaussianKernel", &RegressionTest::GaussianKernel));
    m_mapping.insert(std::make_pair("MargrabeOption", &RegressionTest::MargrabeOptionVasicek));
    m_mapping.insert(std::make_pair("PlayerResults", &RegressionTest::PlayerResultTest));
    m_mapping.insert(std::make_pair("DummyTournament", &RegressionTest::DummyTournament));
}

RegressionTestLauncher::RegressionTestLauncher(std::ostream & out) : RegressionTest(out)
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
        result = ((*this).*(it->second))();
        if (!result)
        {
            return result;
        }
        m_out << std::endl;
    }
    return result;
}