//
//  PolynomialRegression.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 28/07/13.
//
//

#ifndef __CVATools__PolynomialRegression__
#define __CVATools__PolynomialRegression__

#include <iostream>
#include "LinearRegression.h"

namespace Maths
{
    struct PolyRegPms
    {
        std::vector<std::vector<std::size_t> > sPowerAndRegVariables;
        
        virtual void Fill(const std::vector<std::size_t> & dRegressionPower,
                          bool bCrossTerms);
        virtual ~PolyRegPms();
    };
    
    class PolynomialRegression : public LinearRegression
    {
    protected:
        PolyRegPms sPolyRegPms_;
        
    public:
        PolynomialRegression(bool bAddConstantInRegression, const std::vector<std::size_t> & dRegressionPower, bool bCrossTerms);
        PolynomialRegression(bool bAddConstantInRegression, const std::string & cRegressionPower, char cDelimitor = ';');
        virtual ~PolynomialRegression();
        
        virtual Utilities::Matrix ComputeCovarianceMatrix(const Utilities::RegressionData & sRegressionData) const;
        
        //  Update Predicted Values method as the variables are not any more the same
        virtual std::vector<double> GetPredictedValues(const Utilities::RegressionData & sRegressionData,
                                                       const std::vector<double> & sResponse) const;
    };
}

#endif /* defined(__CVATools__PolynomialRegression__) */
