//
//  LeastSquareRegression.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 27/07/13.
//
//

#include "LeastSquareRegression.h"
#include "Exception.h"
#include "Statistics.h"
#include "Matrix.h"

namespace Maths
{
    Utilities::MyVector<double> LeastSquareRegression::ComputeRegCoefs(const Utilities::RegressionData & sRegressionData,
                                                                       const Utilities::MyVector<double> & sResponse) const
    {
        Utilities::Matrix<double> sCovarianceMatrix = ComputeCovarianceMatrix(sRegressionData);
        std::size_t iNVars = sRegressionData.GetNbVariables(), iNObservations = sRegressionData.GetNbObservations();
        Utilities::Matrix<double> sInverse(iNVars, iNVars);
        Utilities::matrixinverse(sInverse, sCovarianceMatrix);
        
        Utilities::MyVector<double> dProjResponse(iNVars, 0.0);
        for (std::size_t iVar = 0 ; iVar < iNVars ; ++iVar)
        {
            for (std::size_t i = 0 ; i < iNObservations ; ++i)
            {
                dProjResponse.at(iVar) += sRegressionData(i, iVar) * sResponse.at(i);
            }
        }
        
        Utilities::MyVector<double> dRegCoefs(iNVars, 0.0);
        for (std::size_t iVar = 0 ; iVar < iNVars ; ++iVar)
        {
            for (std::size_t jVar = 0 ; jVar < iNVars ; ++iVar)
            {
                dRegCoefs.at(iVar) += sInverse(iVar, jVar) * dProjResponse.at(iVar);
            }
        }
        return dRegCoefs;
    }
    
    std::vector<double> LeastSquareRegression::ComputeRegCoefs(const Utilities::RegressionData & sRegressionData,
                                                               const std::vector<double> & sResponse) const
    {
        Utilities::Matrix<double> sCovarianceMatrix = ComputeCovarianceMatrix(sRegressionData);
        std::size_t iNObservations = sRegressionData.GetNbObservations(), iNVars = sCovarianceMatrix.getcols();
        std::size_t iNVarsReg = sRegressionData.GetNbVariables();
        Utilities::Matrix<double> sInverse(iNVars, iNVars);
        Utilities::matrixinverse(sInverse, sCovarianceMatrix);
        
        std::vector<double> dProjResponse(iNVars, 0.0);
        //  Check if the regression data structure has the same number of variables as the number of rows of the covariance matrix
        //  If not, a constant has been added in the regression
        if (iNVars == iNVarsReg)
        {
            for (std::size_t iVar = 0 ; iVar < iNVars ; ++iVar)
            {
                for (std::size_t i = 0 ; i < iNObservations ; ++i)
                {
                    dProjResponse.at(iVar) += sRegressionData(i, iVar) * sResponse.at(i);
                }
                dProjResponse.at(iVar) /= iNObservations;
            }
        }
        else if (iNVars == iNVarsReg + 1)
        {
            for (std::size_t iVar = 0 ; iVar < iNVars - 1 ; ++iVar)
            {
                for (std::size_t i = 0 ; i < iNObservations ; ++i)
                {
                    dProjResponse.at(iVar) += sRegressionData(i, iVar) * sResponse.at(i);
                }
                dProjResponse.at(iVar) /= iNObservations;
            }
            dProjResponse.at(iNVars - 1) = Statistics::Mean(sResponse);
        }
        else
        {
            throw EXCEPTION("Could not check the number of variables : must input a valid number of variables");
        }
        
        std::vector<double> dRegCoefs(iNVars, 0.0);
        Utilities::mult(dRegCoefs, sInverse, dProjResponse);
        
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
                dPredictedValues.at(i) += sRegressionData(i, iVar) * dRegCoefs.at(iVar);
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