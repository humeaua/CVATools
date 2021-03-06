/* 
                 __________                                      
    _____   __ __\______   \_____  _______  ______  ____ _______ 
   /     \ |  |  \|     ___/\__  \ \_  __ \/  ___/_/ __ \\_  __ \
  |  Y Y  \|  |  /|    |     / __ \_|  | \/\___ \ \  ___/ |  | \/
  |__|_|  /|____/ |____|    (____  /|__|  /____  > \___  >|__|   
        \/                       \/            \/      \/        

  Copyright (C) 2011 Ingo Berg

  Permission is hereby granted, free of charge, to any person obtaining a copy of this 
  software and associated documentation files (the "Software"), to deal in the Software
  without restriction, including without limitation the rights to use, copy, modify, 
  merge, publish, distribute, sublicense, and/or sell copies of the Software, and to 
  permit persons to whom the Software is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all copies or 
  substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
  NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. 
*/
#include "muParser.h"
#include "MathFunctions.h"
#include "Require.h"

//--- Standard includes ------------------------------------------------------------------------
#include <cmath>
#include <algorithm>
#include <numeric>

/** \brief Pi (what else?). */
#define PARSER_CONST_PI  3.141592653589793238462643

/** \brief The eulerian number. */
#define PARSER_CONST_E   2.718281828459045235360287

/** \file
    \brief Implementation of the standard floating point parser.
*/


/** \brief Namespace for mathematical applications. */
namespace mu
{
  //---------------------------------------------------------------------------
  // Trigonometric function
  value_type Parser::Sin(value_type v)   { return sin(v);  }
  value_type Parser::Cos(value_type v)   { return cos(v);  }
  value_type Parser::Tan(value_type v)   { return tan(v);  }
  value_type Parser::ASin(value_type v)  { return asin(v); }
  value_type Parser::ACos(value_type v)  { return acos(v); }
  value_type Parser::ATan(value_type v)  { return atan(v); }
  value_type Parser::Sinh(value_type v)  { return sinh(v); }
  value_type Parser::Cosh(value_type v)  { return cosh(v); }
  value_type Parser::Tanh(value_type v)  { return tanh(v); }
  value_type Parser::ASinh(value_type v) { return log(v + sqrt(v * v + 1)); }
  value_type Parser::ACosh(value_type v) { return log(v + sqrt(v * v - 1)); }
  value_type Parser::ATanh(value_type v) { return ((value_type)0.5 * log((1 + v) / (1 - v))); }

  //---------------------------------------------------------------------------
  // Logarithm functions
  value_type Parser::Log2(value_type v)  { return log(v)/log((value_type)2); } // Logarithm base 2
  value_type Parser::Log10(value_type v) { return log10(v); } // Logarithm base 10
  value_type Parser::Ln(value_type v)    { return log(v);   } // Logarithm base e (natural logarithm)

  //---------------------------------------------------------------------------
  //  misc
  value_type Parser::Exp(value_type v)  { return exp(v);   }
  value_type Parser::Abs(value_type v)  { return fabs(v);  }
  value_type Parser::Sqrt(value_type v) { return sqrt(v);  }
  value_type Parser::Rint(value_type v) { return floor(v + (value_type)0.5); }
  value_type Parser::Sign(value_type v) { return (value_type)((v<0) ? -1 : (v>0) ? 1 : 0); }
    
  //---------------------------------------------------------------------------
  // finance functions
  value_type Parser::Norm(value_type x) { return Maths::AccCumNorm(x); }
    
  value_type Parser::BS(value_type Forward, value_type Strike, value_type Maturity, value_type Volatility, string_type CallPut)
  {
      REQUIREEXCEPTION(Forward > 0.0, "Forward is negative");
      REQUIREEXCEPTION(Strike > 0.0, "Strike is negative");
      value_type StdDev = Volatility * sqrt(Maturity);
      
      int iCallPut = CallPut == "Call" || CallPut == "CALL" ? 1 : -1;
      value_type d1 = log(Forward / Strike) / (StdDev) + 0.5 * StdDev;
      return StdDev == 0.0 ? std::max(iCallPut * (Forward - Strike), 0.0) : iCallPut * Forward * Maths::AccCumNorm(iCallPut * d1) - iCallPut * Strike * Maths::AccCumNorm(iCallPut * (d1 - StdDev));
  }
    
    value_type Parser::BSN(value_type Forward, value_type Strike, value_type Maturity, value_type Volatility, string_type CallPut)
    {
        value_type StdDev = Volatility * sqrt(Maturity);
        value_type d1 = (Forward - Strike) / StdDev;
        int iCallPut = CallPut == "Call" || CallPut == "CALL" ? 1 : -1;
        
        return StdDev == 0.0 ? std::max(iCallPut * (Forward - Strike), 0.0) : iCallPut * (Forward - Strike) * Maths::AccCumNorm(d1) + StdDev / sqrt(2.0 * PARSER_CONST_PI) * exp(0.5 * d1 * d1);
    }
    
    value_type Parser::CallSpread(value_type x, value_type k, value_type epsilon, string_type BuySell)
    {
        // Conservative solution
        REQUIREEXCEPTION(epsilon > 0, "Epsilon is negative");
        if (BuySell == "SELL")
        {
            if (x < k)
                return 0.0;
            else if (x > k + epsilon)
                return 1;
            else
                return (k + epsilon - x) / epsilon;
        }
        else
        {
            if (x < k - epsilon)
                return 0.0;
            else if (x > k)
                return 1.0;
            else
                return (k - epsilon - x) / epsilon;
        }
    }
    
    value_type Parser::PutSpread(value_type x, value_type k, value_type epsilon, string_type BuySell)
    {
        // Conservative solution
        if (BuySell == "SELL")
        {
            if (x < k)
                return 1.0;
            else if (x > k + epsilon)
                return 0.0;
            else
                return -(k + epsilon - x) / epsilon;
        }
        else
        {
            if (x < k - epsilon)
                return 1.0;
            else if (x > k)
                return 0.0;
            else
                return -(k - epsilon - x) / epsilon;
        }
    }

  //---------------------------------------------------------------------------
  /** \brief Callback for the unary minus operator.
      \param v The value to negate
      \return -v
  */
  value_type Parser::UnaryMinus(value_type v) 
  { 
    return -v; 
  }

  //---------------------------------------------------------------------------
  /** \brief Callback for adding multiple values. 
      \param [in] a_afArg Vector with the function arguments
      \param [in] a_iArgc The size of a_afArg
  */
  value_type Parser::Sum(const value_type *a_afArg, int a_iArgc)
  { 
    if (!a_iArgc)	
      throw exception_type(_T("too few arguments for function sum."));

    value_type fRes=0;
    for (int i=0; i<a_iArgc; ++i) fRes += a_afArg[i];
    return fRes;
  }

  //---------------------------------------------------------------------------
  /** \brief Callback for averaging multiple values. 
      \param [in] a_afArg Vector with the function arguments
      \param [in] a_iArgc The size of a_afArg
  */
  value_type Parser::Avg(const value_type *a_afArg, int a_iArgc)
  { 
    if (!a_iArgc)	
      throw exception_type(_T("too few arguments for function sum."));

    value_type fRes=0;
    for (int i=0; i<a_iArgc; ++i) fRes += a_afArg[i];
    return fRes/(value_type)a_iArgc;
  }


  //---------------------------------------------------------------------------
  /** \brief Callback for determining the minimum value out of a vector. 
      \param [in] a_afArg Vector with the function arguments
      \param [in] a_iArgc The size of a_afArg
  */
  value_type Parser::Min(const value_type *a_afArg, int a_iArgc)
  { 
      if (!a_iArgc)	
          throw exception_type(_T("too few arguments for function min."));

      value_type fRes=a_afArg[0];
      for (int i=1; i<a_iArgc; ++i) fRes = std::min(fRes, a_afArg[i]);

      return fRes;
  }


  //---------------------------------------------------------------------------
  /** \brief Callback for determining the maximum value out of a vector. 
      \param [in] a_afArg Vector with the function arguments
      \param [in] a_iArgc The size of a_afArg
  */
  value_type Parser::Max(const value_type *a_afArg, int a_iArgc)
  { 
    if (!a_iArgc)	
      throw exception_type(_T("too few arguments for function min."));

    value_type fRes=a_afArg[0];
    for (int i=1; i<a_iArgc; ++i) fRes = std::max(fRes, a_afArg[i]);

    return fRes;
  }


  //---------------------------------------------------------------------------
  /** \brief Default value recognition callback. 
      \param [in] a_szExpr Pointer to the expression
      \param [in, out] a_iPos Pointer to an index storing the current position within the expression
      \param [out] a_fVal Pointer where the value should be stored in case one is found.
      \return 1 if a value was found 0 otherwise.
  */
  int Parser::IsVal(const char_type* a_szExpr, int *a_iPos, value_type *a_fVal)
  {
    value_type fVal(0);

    stringstream_type stream(a_szExpr);
    stream.seekg(0);        // todo:  check if this really is necessary
    stream.imbue(Parser::s_locale);
    stream >> fVal;
    stringstream_type::pos_type iEnd = stream.tellg(); // Position after reading

    if (iEnd==(stringstream_type::pos_type)-1)
      return 0;

    *a_iPos += (int)iEnd;
    *a_fVal = fVal;
    return 1;
  }


  //---------------------------------------------------------------------------
  /** \brief Constructor. 

    Call ParserBase class constructor and trigger Function, Operator and Constant initialization.
  */
  Parser::Parser()
    :ParserBase()
  {
    AddValIdent(IsVal);

    InitCharSets();
    InitFun();
    InitConst();
    InitOprt();
  }

  //---------------------------------------------------------------------------
  /** \brief Define the character sets. 
      \sa DefineNameChars, DefineOprtChars, DefineInfixOprtChars
    
    This function is used for initializing the default character sets that define
    the characters to be useable in function and variable names and operators.
  */
  void Parser::InitCharSets()
  {
    DefineNameChars( _T("0123456789_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") );
    DefineOprtChars( _T("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ+-*^/?<>=#!$%&|~'_{}") );
    DefineInfixOprtChars( _T("/+-*^?<>=#!$%&|~'_") );
  }

  //---------------------------------------------------------------------------
  /** \brief Initialize the default functions. */
  void Parser::InitFun()
  {
      // trigonometric functions
      DefineFun(_T("SIN"), Sin);
      DefineFun(_T("COS"), Cos);
      DefineFun(_T("TAN"), Tan);
      // arcus functions
      DefineFun(_T("ASIN"), ASin);
      DefineFun(_T("ACOS"), ACos);
      DefineFun(_T("ATAN"), ATan);
      // hyperbolic functions
      DefineFun(_T("SINH"), Sinh);
      DefineFun(_T("COSH"), Cosh);
      DefineFun(_T("TANH"), Tanh);
      // arcus hyperbolic functions
      DefineFun(_T("ASINH"), ASinh);
      DefineFun(_T("ACOSH"), ACosh);
      DefineFun(_T("ATANH"), ATanh);
      // Logarithm functions
      DefineFun(_T("LOG2"), Log2);
      DefineFun(_T("LOG10"), Log10);
      DefineFun(_T("LOG"), Log10);
      DefineFun(_T("LN"), Ln);
      // misc
      DefineFun(_T("EXP"), Exp);
      DefineFun(_T("SQRT"), Sqrt);
      DefineFun(_T("SIGN"), Sign);
      DefineFun(_T("RINT"), Rint);
      DefineFun(_T("ABS"), Abs);
      // To change the number of args
      // finance functions
      DefineFun(_T("ACCCUMNORM"), Maths::AccCumNorm);
      DefineFun(_T("BS"), BS);
      DefineFun(_T("BSN"), BSN);
      DefineFun(_T("CALLSPREAD"), CallSpread);
      DefineFun(_T("PUTSPREAD"), PutSpread);
      
      // Functions with variable number of arguments
      DefineFun(_T("SUM"), Sum);
      DefineFun(_T("AVG"), Avg);
      DefineFun(_T("MIN"), Min);
      DefineFun(_T("MAX"), Max);
  }

  //---------------------------------------------------------------------------
  /** \brief Initialize constants.
  
    By default the parser recognizes two constants. Pi ("pi") and the eulerian
    number ("_e").
  */
  void Parser::InitConst()
  {
    DefineConst(_T("_PI"), (value_type)PARSER_CONST_PI);
    DefineConst(_T("_E"), (value_type)PARSER_CONST_E);
  }

  //---------------------------------------------------------------------------
  /** \brief Initialize operators. 
  
    By default only the unary minus operator is added.
  */
  void Parser::InitOprt()
  {
    DefineInfixOprt(_T("-"), UnaryMinus);
  }

  //---------------------------------------------------------------------------
  void Parser::OnDetectVar(string_type * /*pExpr*/, int & /*nStart*/, int & /*nEnd*/)
  {
    // this is just sample code to illustrate modifying variable names on the fly.
    // I'm not sure anyone really needs such a feature...
    /*


    string sVar(pExpr->begin()+nStart, pExpr->begin()+nEnd);
    string sRepl = std::string("_") + sVar + "_";
  
    int nOrigVarEnd = nEnd;
    cout << "variable detected!\n";
    cout << "  Expr: " << *pExpr << "\n";
    cout << "  Start: " << nStart << "\n";
    cout << "  End: " << nEnd << "\n";
    cout << "  Var: \"" << sVar << "\"\n";
    cout << "  Repl: \"" << sRepl << "\"\n";
    nEnd = nStart + sRepl.length();
    cout << "  End: " << nEnd << "\n";
    pExpr->replace(pExpr->begin()+nStart, pExpr->begin()+nOrigVarEnd, sRepl);
    cout << "  New expr: " << *pExpr << "\n";
    */
  }

  //---------------------------------------------------------------------------
  /** \brief Numerically differentiate with regard to a variable. 
      \param [in] a_Var Pointer to the differentiation variable.
      \param [in] a_fPos Position at which the differentiation should take place.
      \param [in] a_fEpsilon Epsilon used for the numerical differentiation.

    Numerical differentiation uses a 5 point operator yielding a 4th order 
    formula. The default value for epsilon is 0.00074 which is
    numeric_limits<double>::epsilon() ^ (1/5) as suggested in the muparser
    forum:

    http://sourceforge.net/forum/forum.php?thread_id=1994611&forum_id=462843
  */
  value_type Parser::Diff(value_type *a_Var, 
                          value_type  a_fPos, 
                          value_type  a_fEpsilon) const
  {
    value_type fRes(0), 
               fBuf(*a_Var),
               f[4] = {0,0,0,0},
               fEpsilon(a_fEpsilon);

    // Backwards compatible calculation of epsilon inc case the user doesnt provide
    // his own epsilon
    if (fEpsilon==0)
      fEpsilon = (a_fPos==0) ? (value_type)1e-10 : (value_type)1e-7 * a_fPos;

    *a_Var = a_fPos+2 * fEpsilon;  f[0] = Eval();
    *a_Var = a_fPos+1 * fEpsilon;  f[1] = Eval();
    *a_Var = a_fPos-1 * fEpsilon;  f[2] = Eval();
    *a_Var = a_fPos-2 * fEpsilon;  f[3] = Eval();
    *a_Var = fBuf; // restore variable

    fRes = (-f[0] + 8*f[1] - 8*f[2] + f[3]) / (12*fEpsilon);
    return fRes;
  }
} // namespace mu
