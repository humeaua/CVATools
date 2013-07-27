//
//  LeastSquareRegression.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 27/07/13.
//
//

#include "LeastSquareRegression.h"

namespace Maths
{
    Utilities::MyVector<double> LeastSquareRegression::ComputeRegCoefs(const Utilities::RegressionData & sRegressionData,
                                                                       const Utilities::MyVector<double> & sResponse) const
    {
        Utilities::Matrix sCovarianceMatrix = ComputeCovarianceMatrix(sRegressionData);
        std::size_t iNVars = sRegressionData.GetNbVariables(), iNObservations = sRegressionData.GetNbObservations();
        Utilities::Matrix sInverse(iNVars, iNVars);
        Utilities::matrixinverse(sInverse, sCovarianceMatrix);
        
        Utilities::MyVector<double> dProjResponse(iNVars, 0.0);
        for (std::size_t iVar = 0 ; iVar < iNVars ; ++iVar)
        {
            for (std::size_t i = 0 ; i < iNObservations ; ++i)
            {
                dProjResponse[iVar] += sRegressionData(i, iVar) * sResponse[i];
            }
        }
        
        Utilities::MyVector<double> dRegCoefs(iNVars, 0.0);
        for (std::size_t iVar = 0 ; iVar < iNVars ; ++iVar)
        {
            for (std::size_t jVar = 0 ; jVar < iNVars ; ++iVar)
            {
                dRegCoefs[iVar] += sInverse(iVar, jVar) * dProjResponse[iVar];
            }
        }
        return dRegCoefs;
    }
    
    std::vector<double> LeastSquareRegression::ComputeRegCoefs(const Utilities::RegressionData & sRegressionData,
                                                               const std::vector<double> & sResponse) const
    {
        Utilities::Matrix sCovarianceMatrix = ComputeCovarianceMatrix(sRegressionData);
        std::size_t iNObservations = sRegressionData.GetNbObservations(), iNVars = sCovarianceMatrix.getcols();
        Utilities::Matrix sInverse(iNVars, iNVars);
        Utilities::matrixinverse(sInverse, sCovarianceMatrix);
        
        std::vector<double> dProjResponse(iNVars, 0.0);
        for (std::size_t iVar = 0 ; iVar < iNVars ; ++iVar)
        {
            for (std::size_t i = 0 ; i < iNObservations ; ++i)
            {
                dProjResponse[iVar] += sRegressionData(i, iVar) * sResponse[i];
            }
            dProjResponse[iVar] /= iNObservations;
        }
        
        std::vector<double> dRegCoefs(iNVars, 0.0);
        for (std::size_t iVar = 0 ; iVar < iNVars ; ++iVar)
        {
            for (std::size_t jVar = 0 ; jVar < iNVars ; ++iVar)
            {
                dRegCoefs[iVar] += sInverse(iVar, jVar) * dProjResponse[iVar];
            }
        }
        return dRegCoefs;
    }

    //  Methods from Base Class RegressionMethod in both std::vector and Utilites::MyVector
    std::vector<double> LeastSquareRegression::GetPredictedValues(const Utilities::RegressionData & sRegressionData,
                                                                  const std::vector<double> & sResponse) const
    {
        std::size_t iNVars = sRegressionData.GetNbVariables(), iNObservations = sRegressionData.GetNbObservations();
        std::vector<double> dPredictedValues(iNObservations, 0.0), dRegCoefs = ComputeRegCoefs(sRegressionData, sResponse);
        
        for (std::size_t i = 0 ; i < iNObservations ; ++i)
        {
            for (std::size_t iVar = 0 ; iVar < iNVars ; ++iVar)
            {
                dPredictedValues[i] += sRegressionData(i, iVar) * dRegCoefs[iVar];
            }
        }
        return dPredictedValues;
    }
    
    Utilities::MyVector<double> LeastSquareRegression::GetPredictedValues(const Utilities::RegressionData & sRegressionData,
                                                                          const Utilities::MyVector<double> & sResponse) const
    {
        return GetPredictedValues(sRegressionData, sResponse);
    }
}