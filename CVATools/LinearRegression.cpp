//
//  LinearRegression.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 27/07/13.
//
//

#include "LinearRegression.h"

namespace Maths
{
    LinearRegression::LinearRegression(bool bAddConstantInRegression) : bAddConstantInRegression_(bAddConstantInRegression)
    {}
    
    Utilities::Matrix LinearRegression::ComputeCovarianceMatrix(const Utilities::RegressionData &sRegressionData) const
    {
        std::size_t iNVars = sRegressionData.GetNbVariables(), iNVarsLoc = iNVars + (bAddConstantInRegression_ ? 1 : 0), iNObservations = sRegressionData.GetNbObservations();
        Utilities::Matrix sCovarianceMatrix(iNVarsLoc, iNVarsLoc);
        
        double ** dMatrix = new double*[iNVarsLoc];
        for (std::size_t i = 0 ; i < iNVarsLoc ; ++i)
        {
            dMatrix[i] = new double[iNVarsLoc];
        }
        
        if (bAddConstantInRegression_)
        {
            dMatrix[iNVars][iNVars] = 1.0;
            
            for (std::size_t iVar = 0 ; iVar < iNVars ; ++iVar)
            {
                dMatrix[iVar][iNVars] = 0;
                for (std::size_t i = 0 ; i < iNObservations ; ++i)
                {
                    dMatrix[iVar][iNVars] += sRegressionData(i,iVar);
                }
                dMatrix[iVar][iNVars] /= iNObservations;
                dMatrix[iNVars][iVar] = dMatrix[iVar][iNVars];
            }
        }
        
        for (std::size_t iVar = 0 ; iVar < iNVars ; ++iVar)
        {
            dMatrix[iVar][iVar] = 0;
            for (std::size_t i = 0 ; i < iNObservations ; ++i)
            {
                dMatrix[iVar][iVar] += sRegressionData(i,iVar) * sRegressionData(i,iVar);
            }
            dMatrix[iVar][iVar] /= iNObservations;
        }
        
        for (std::size_t iVar = 0 ; iVar < iNVars ; ++iVar)
        {
            for (std::size_t jVar = iVar + 1 ; jVar < iNVars ; ++jVar)
            {
                dMatrix[iVar][jVar] = 0;
                for (std::size_t i = 0 ; i < iNObservations ; ++i)
                {
                    dMatrix[iVar][jVar] += sRegressionData(i,iVar) * sRegressionData(i, jVar);
                }
                dMatrix[iVar][jVar] /= iNObservations;
                dMatrix[jVar][iVar] = dMatrix[iVar][jVar];
            }
        }
        
    FREE_RETURN:
        for (std::size_t i = 0 ; i < iNVars ; ++i)
        {
            delete[] dMatrix[i];
        }
        delete[] dMatrix;
        
        return sCovarianceMatrix;
    }
    
    std::vector<double> LinearRegression::GetPredictedValues(const Utilities::RegressionData & sRegressionData,
                                                                  const std::vector<double> & sResponse) const
    {
        std::size_t iNVars = sRegressionData.GetNbVariables(), iNObservations = sRegressionData.GetNbObservations();
        std::vector<double> dPredictedValues(iNObservations, 0.0), dRegCoefs = ComputeRegCoefs(sRegressionData, sResponse);
        iNVars -= bAddConstantInRegression_ ? 1 : 0;
        
        for (std::size_t i = 0 ; i < iNObservations ; ++i)
        {
            if (bAddConstantInRegression_)
            {
                dPredictedValues[i] = dRegCoefs.back();
            }
            for (std::size_t iVar = 0 ; iVar < iNVars ; ++iVar)
            {
                dPredictedValues[i] += sRegressionData(i, iVar) * dRegCoefs[iVar];
            }
        }
        return dPredictedValues;
    }
}