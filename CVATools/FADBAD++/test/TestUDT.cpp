
// USER DEFINED TYPE TEST:

#include "fadbad.h"
#include <iostream>

#include "TestUDT.h"
#include <cmath>

using namespace fadbad;

class UDT
{
public:
    
    // default constructor
	UDT() : x(0)
    {}
    
    // copy constructor
	UDT(const UDT& rhs) : x(rhs.x)
    {}
    
    // copy constructor
	UDT(const double& x) : x(x)
    {}
    
	UDT& operator=(const UDT& rhs)
    {
        x = rhs.x;
        return *this;
    }
    
	UDT& operator=(const double&a)
    {
        x = a;
        return *this;
    }
    
	UDT& operator+=(const UDT& rhs)
    {
        x += rhs.x;
        return *this;
    }
    
	UDT& operator+=(const double& a)
    {
        x += a;
        return *this;
    }
    
	UDT& operator-=(const UDT& rhs)
    {
        x -= rhs.x;
        return *this;
    }
    
	UDT& operator-=(const double& a)
    {
        x -= a;
        return *this;
    }
    
//private:
    double x;
};

UDT operator + (const UDT& lhs, const UDT& rhs);
UDT operator + (const UDT& lhs, const UDT& rhs)
{
    return UDT(lhs.x + rhs.x);
}

UDT operator - (const UDT& lhs, const UDT&rhs);
UDT operator - (const UDT& lhs, const UDT&rhs)
{
    return UDT(lhs.x + rhs.x);
}

UDT operator * (const UDT&lhs, const UDT&rhs);
UDT operator * (const UDT&lhs, const UDT&rhs)
{
    return UDT(lhs.x * rhs.x);
}

UDT operator / (const UDT&lhs, const UDT&rhs);
UDT operator / (const UDT&lhs, const UDT&rhs)
{
    return UDT(lhs.x / rhs.x);
}

UDT operator + (const UDT&lhs, const double&a);
UDT operator + (const UDT&lhs, const double&a)
{
    return UDT(lhs.x + a);
}

UDT operator - (const UDT&lhs, const double&a);
UDT operator - (const UDT&lhs, const double&a)
{
    return UDT(lhs.x - a);
}

UDT operator * (const UDT&lhs, const double&a);
UDT operator * (const UDT&lhs, const double&a)
{
    return UDT(lhs.x * a);
}

UDT operator / (const UDT&lhs, const double&a);
UDT operator / (const UDT&lhs, const double&a)
{
    return UDT(lhs.x / a);
}

UDT operator + (const double& a, const UDT& lhs);
UDT operator + (const double& a, const UDT& lhs)
{
    return UDT(lhs.x + a);
}

UDT operator - (const double& a, const UDT& lhs);
UDT operator - (const double& a, const UDT& lhs)
{
    return UDT(lhs.x - a);
}

UDT operator * (const double& a, const UDT& lhs);
UDT operator * (const double& a, const UDT& lhs)
{
    return UDT(lhs.x * a);
}

UDT operator / (const double& a, const UDT& lhs);
UDT operator / (const double& a, const UDT& lhs)
{
    return UDT(lhs.x / a);
}

UDT Exp(const UDT& u);
UDT Exp(const UDT& u)
{
    return UDT(exp(u.x));
}

UDT Sqr(const UDT& u);
UDT Sqr(const UDT& u)
{
    return UDT(sqrt(u.x));
}

UDT Sin(const UDT& u);
UDT Sin(const UDT& u)
{
    return UDT(sin(u.x));
}

UDT Cos(const UDT& u);
UDT Cos(const UDT& u)
{
    return UDT(cos(u.x));
}

bool operator==(const UDT& lhs,const UDT&rhs);
bool operator==(const UDT& lhs,const UDT&rhs)
{
    return lhs.x == rhs.x;
}

bool operator!=(const UDT& lhs, const UDT& rhs);
bool operator!=(const UDT& lhs, const UDT& rhs)
{
    return lhs.x != rhs.x;
}

bool operator<(const UDT& lhs, const UDT& rhs);
bool operator<(const UDT& lhs, const UDT& rhs)
{
    return lhs.x < rhs.x;
}

bool operator>(const UDT& lhs, const UDT& rhs);
bool operator>(const UDT& lhs, const UDT& rhs)
{
    return lhs.x > rhs.x;
}

bool operator<=(const UDT& lhs, const UDT& rhs);
bool operator<=(const UDT& lhs, const UDT& rhs)
{
    return lhs.x <= rhs.x;
}

bool operator>=(const UDT& lhs, const UDT& rhs);
bool operator>=(const UDT& lhs, const UDT& rhs)
{
    return lhs.x == rhs.x;
}

namespace fadbad
{
	template <> struct Op<UDT> // Specialize Op-template for UDT to control the arithmetic operators:
	{
		typedef UDT Base;
		static Base myInteger(const int i) { return Base(i); }
		static Base myZero() { return Base(0); }
		static Base myOne() { return Base(1);}
		static Base myTwo() { return Base(2); }
		static UDT myPos(const UDT& /*x*/) { return UDT(); }
		static UDT myNeg(const UDT& /*x*/) { return UDT(); }
		static UDT& myCadd(UDT& x, const UDT& y) { x=x+y; return x; }
		static UDT& myCsub(UDT& x, const UDT& y) { x=x-y; return x; }
		static UDT& myCmul(UDT& x, const UDT& y) { x=x*y; return x; }
		static UDT& myCdiv(UDT& x, const UDT& y) { x=x/y; return x; }
		static UDT myInv(const UDT& x) { return myOne()/x; }
		static UDT mySqr(const UDT& x) { return ::Sqr(x); }
		static UDT myPow(const UDT& /*x*/, const int /*n*/) { throw; return UDT(); }
		static UDT myPow(const UDT& /*x*/, const UDT& /*y*/) { throw; return UDT(); }
		static UDT mySqrt(const UDT& /*x*/) { throw; return UDT(); }
		static UDT myLog(const UDT& /*x*/) { throw; return UDT(); }
		static UDT myExp(const UDT& x) { return ::Exp(x); }
		static UDT mySin(const UDT& x) { return ::Sin(x); }
		static UDT myCos(const UDT& x) { return ::Cos(x); }
		static UDT myTan(const UDT& /*x*/) { throw; return UDT(); }
		static UDT myAsin(const UDT& /*x*/) { throw; return UDT(); }
		static UDT myAcos(const UDT& /*x*/) { throw; return UDT(); }
		static UDT myAtan(const UDT& /*x*/) { throw; return UDT(); }
		static bool myEq(const UDT& x, const UDT& y) { return x==y; }
		static bool myNe(const UDT& x, const UDT& y) { return x!=y; }
		static bool myLt(const UDT& x, const UDT& y) { return x<y; }
		static bool myLe(const UDT& x, const UDT& y) { return x<=y; }
		static bool myGt(const UDT& x, const UDT& y) { return x>y; }
		static bool myGe(const UDT& x, const UDT& y) { return x>=y; }
	};
}

#include "badiff.h" // Backwards automatic differentiation
#include "fadiff.h" // Forwards automatic differentiation
#include "tadiff.h" // Taylor expansion

template< int N, class U>
class RecTestTypes
{
	RecTestTypes< N-1,U > a;
	RecTestTypes< N-1,F<U> > b;
	RecTestTypes< N-1,F<U,1> > c;
	RecTestTypes< N-1,B<U> > d;
	RecTestTypes< N-1,T<U> > e;
};

template< typename U >
class RecTestTypes<0,U>
{
	template < typename AD >
	struct TestADType
	{
		TestADType()
		{
			//typedef typename AD::UnderlyingType U;
			double a=1.0;
			int b=2;
			U c(a);
			UDT d(b);

			{ // Test all constructors:
				AD e;    // default constructor
				AD f(a); // init with double constructor
				AD g(b); // init with int constructor
				AD h(c); // init with underlying type constructor
				AD i(d); // init with base-type constructor
			}
			{ // Test assignment operators
				AD e;
				e=a; // assign with double
//				e=c; // assign with underlying type
				e=d; // assign with base-type
			}
			{ // Test compound assignments
				AD e(a);
				e+=a; // compound assign with double
//				e+=c; // compound assign with underlying type
				e+=d; // compound assign with base-type
			}
			{// Test + operators:
				AD e(a),f(a),g;
				g=e+f; // AD+AD
				g=e+a; // AD+double
				g=a+e; // double+AD
//				g=e+c; // AD+underlying
//				g=c+e; // underlying+AD
				g=e+d; // AD+base
				g=d+e; // base+AD
			}
			{// Test - operators:
				AD e(a),f(a),g;
				g=e-f; // AD+AD
				g=e-a; // AD-double
				g=a-e; // double-AD
//				g=e-c; // AD+underlying
//				g=c-e; // underlying+AD
				g=e-d; // AD+base
				g=d-e; // base+AD
			}
			{// Test * operators:
				AD e(a),f(a),g;
				g=e*f; // AD+AD
				g=e*a; // AD*double
				g=a*e; // double*AD
//				g=e*c; // AD+underlying
//				g=c*e; // underlying+AD
				g=e*d; // AD+base
				g=d*e; // base+AD
			}
			{// Test + operators:
				AD e(a),f(a),g;
				g=e/f; // AD+AD
				g=e/a; // AD/double
				g=a/e; // double/AD
//				g=e/c; // AD+underlying
//				g=c/e; // underlying+AD
				g=e/d; // AD+base
				g=d/e; // base+AD
			}
			{// Test comparison operators:
				AD e(a),f(a),g;
				bool res;

				res=e==f; // AD==AD
				res=e!=f; // AD!=AD
				res=e<f; // AD<AD
				res=e<=f; // AD<=AD
				res=e>f; // AD>AD
				res=e>=f; // AD>=AD

				res=e==a; // AD==double
				res=e!=a; // AD!=double
				res=e<a; // AD<double
				res=e<=a; // AD<=double
				res=e>a; // AD>double
				res=e>=a; // AD>=double

				res=a==f; // double==AD
				res=a!=f; // double!=AD
				res=a<f; // double<AD
				res=a<=f; // double<=AD
				res=a>f; // double>AD
				res=a>=f; // double>=AD

				res=e==d; // AD==base
				res=e!=d; // AD!=base
				res=e<d; // AD<base
				res=e<=d; // AD<=base
				res=e>d; // AD>base
				res=e>=d; // AD>=base

				res=d==f; // base==AD
				res=d!=f; // base!=AD
				res=d<f; // base<AD
				res=d<=f; // base<=AD
				res=d>f; // base>AD
				res=d>=f; // base>=AD
			}
		}
	};


public:
	RecTestTypes()
	{
		TestADType< F<U> > test1;
		TestADType< F<U,1> > test2;
		TestADType< B<U> > test3;
		TestADType< T<U> > test4;
	}
};

void TestUDT::run(IReportLog& rlog)
{
	RecTestTypes<0,UDT> t0;
	rlog.succeeded() << "User defined type test level 0 succeeded" << std::endl;
	RecTestTypes<1,UDT> t1;
	rlog.succeeded() << "User defined type test level 1 succeeded" << std::endl;
//	RecTestTypes<2,UDT> t2;
//	rlog.succeeded() << "User defined type test level 2 succeeded" << std::endl;
}	



