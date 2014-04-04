//
//  EuropeanPayoff.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 28/02/14.
//
//

#ifndef __CVATools__EuropeanPayoff__
#define __CVATools__EuropeanPayoff__

#include <iostream>
#include <vector>
#include "Require.h"

namespace Finance
{
    namespace Payoff
    {
        typedef std::vector<double> DoubleVec;
        
        //  Template class for payoff depending on dimension
        template<size_t dimension>
        class BasePayoff
        {
        public:
            BasePayoff();
            virtual double pay(const DoubleVec & S) const = 0;
            virtual ~BasePayoff();
        private:
            size_t m_dimensions;
        };
        
        template<size_t dimension>
        BasePayoff<dimension>::BasePayoff() : m_dimensions(dimension)
        {}
        
        template<size_t dimension>
        BasePayoff<dimension>::~BasePayoff<dimension>()
        {}
        
        template<size_t dimension>
        double BasePayoff<dimension>::pay(const DoubleVec &S) const
        {
            REQUIREEXCEPTION(S.size() == dimension, "Underlying size and payoff dimension are not matching");
        }
        
        class EuropeanPayoff1 : public BasePayoff<1>
        {
        public:
            double pay(const DoubleVec &S) const; // method already declared virtual in the base class
            virtual ~EuropeanPayoff1();
        protected:
            virtual double pay1(double s1) const = 0;
        };
        
        class EuropeanPayoff2 : public BasePayoff<2>
        {
        public:
            double pay(const DoubleVec &S) const;
            virtual ~EuropeanPayoff2();
        protected:
            virtual double pay2(double s1, double s2) const = 0;
        };

        //Base class for all payoffs
        /*class EuropeanPayoff
        {
        private:
            size_t m_iNDimensions;
            
            virtual double pay1(double s1) const = 0;
            virtual double pay2(double s1, double s2) const = 0;
        public:
            EuropeanPayoff(size_t iNDimensions);
            virtual ~EuropeanPayoff();
            virtual double pay(const std::vector<double> & S) const;
        };*/
    }
}

#endif /* defined(__CVATools__GenericPayoff__) */
