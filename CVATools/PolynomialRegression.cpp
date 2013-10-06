//
//  PolynomialRegression.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 28/07/13.
//
//

#include "PolynomialRegression.h"
#include "StringUtilities.h"
#include <string>
#include <cmath>

namespace Maths
{
    void PolyRegPms::Fill(const std::vector<std::size_t> &dRegressionPower,
                          bool bCrossTerms)
    {
        for (std::size_t iVar = 0 ; iVar < dRegressionPower.size() ; ++iVar)
        {
            std::vector<std::size_t> iVect(4, 0);
            iVect.at(0) = iVect.at(1) = iVar;
            iVect.at(3) = 0;
            for (std::size_t iPower = 1 ; iPower < dRegressionPower.at(iVar) ; ++iPower)
            {
                iVect.at(2) = iPower;
                sPowerAndRegVariables.push_back(iVect);
            }
        }
        if (bCrossTerms)
        {
            for (std::size_t iVar = 0 ; iVar < dRegressionPower.size() ; ++iVar)
            {
                for (std::size_t jVar = iVar + 1 ; jVar < dRegressionPower.size() ; ++jVar)
                {
                    std::vector<std::size_t> iVect(4, 0);
                    iVect.at(0) = iVar;
                    iVect.at(1) = jVar;
                    for (std::size_t iPower = 1 ; iPower < dRegressionPower.at(iVar) ; ++iPower)
                    {
                        for (std::size_t jPower = 1 ; jPower < dRegressionPower.at(jVar) ; ++jPower)
                        {
                            iVect.at(2) = iPower;
                            iVect.at(3) = jPower;
                            sPowerAndRegVariables.push_back(iVect);
                        }
                    }
                }
            }
        }
    }
    
    PolyRegPms::~PolyRegPms()
    {
        for (std::size_t i = 0 ; i < sPowerAndRegVariables.size() ; ++i)
        {
            sPowerAndRegVariables.at(i).clear();
        }
        sPowerAndRegVariables.clear();
    }
    
    PolynomialRegression::PolynomialRegression(bool bAddConstantInRegression,
                                               const std::vector<std::size_t> & dRegressionPower,
                                               bool bCrossTerms) : LinearRegression(bAddConstantInRegression)
    {
        sPolyRegPms_.Fill(dRegressionPower, bCrossTerms);
    }
    
    PolynomialRegression::PolynomialRegression(bool bAddConstantInRegression,
                                               const std::string & cRegressionPower,
                                               char cDelimitor) : LinearRegression(bAddConstantInRegression)
    {
        std::vector<std::string> cString = Utilities::Split(cRegressionPower, cDelimitor);
        std::vector<std::size_t> iRegressionPower(cString.size());
        
        for (std::size_t i = 0 ; i < cString.size() ; ++i)
        {
            //  may pass this to a more relable c++ version of atoi
            iRegressionPower.at(i) = atoi(cString.at(i).c_str());
        }
    }
    
    PolynomialRegression::~PolynomialRegression()
    {
        sPolyRegPms_.~PolyRegPms();
    }
    
    Utilities::Matrix PolynomialRegression::ComputeCovarianceMatrix(const Utilities::RegressionData & sRegressionData) const
    {
        std::size_t iNVars = sPolyRegPms_.sPowerAndRegVariables.size(), iNVarsLoc = iNVars + (bAddConstantInRegression_ ? 1 : 0), iNObservations = sRegressionData.GetNbObservations();
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
                    dMatrix[iVar][iNVars] += pow(sRegressionData(i,sPolyRegPms_.sPowerAndRegVariables.at(iVar).at(0)),sPolyRegPms_.sPowerAndRegVariables.at(iVar).at(2)) * pow(sRegressionData(i,sPolyRegPms_.sPowerAndRegVariables.at(iVar).at(1)),sPolyRegPms_.sPowerAndRegVariables.at(iVar).at(3));
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
                double dVar = pow(sRegressionData(i,sPolyRegPms_.sPowerAndRegVariables.at(iVar).at(0)),sPolyRegPms_.sPowerAndRegVariables.at(iVar).at(2)) * pow(sRegressionData(i,sPolyRegPms_.sPowerAndRegVariables.at(iVar).at(1)),sPolyRegPms_.sPowerAndRegVariables.at(iVar).at(3));
                dMatrix[iVar][iVar] += dVar * dVar;
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
                    double dVar1 = pow(sRegressionData(i,sPolyRegPms_.sPowerAndRegVariables.at(iVar).at(0)),sPolyRegPms_.sPowerAndRegVariables.at(iVar).at(2)) * pow(sRegressionData(i,sPolyRegPms_.sPowerAndRegVariables.at(iVar).at(1)),sPolyRegPms_.sPowerAndRegVariables.at(iVar).at(3)),
                    dVar2 = pow(sRegressionData(i,sPolyRegPms_.sPowerAndRegVariables.at(iVar).at(0)),sPolyRegPms_.sPowerAndRegVariables.at(iVar).at(2)) * pow(sRegressionData(i,sPolyRegPms_.sPowerAndRegVariables.at(iVar).at(1)),sPolyRegPms_.sPowerAndRegVariables.at(iVar).at(3));
                    dMatrix[iVar][jVar] += dVar1 * dVar2;
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
    
    std::vector<double> PolynomialRegression::GetPredictedValues(const Utilities::RegressionData & sRegressionData,
                                                   const std::vector<double> & sResponse) const
    {
        std::size_t iNVars = sPolyRegPms_.sPowerAndRegVariables.size(), iNObservations = sRegressionData.GetNbObservations();
        std::vector<double> dPredictedValues(iNObservations, 0.0), dRegCoefs = ComputeRegCoefs(sRegressionData, sResponse);
        iNVars -= bAddConstantInRegression_ ? 1 : 0;
        
        for (std::size_t i = 0 ; i < iNObservations ; ++i)
        {
            if (bAddConstantInRegression_)
            {
                dPredictedValues.at(i) = dRegCoefs.back();
            }
            for (std::size_t iVar = 0 ; iVar < iNVars ; ++iVar)
            {
                dPredictedValues.at(i) += pow(sRegressionData(i,sPolyRegPms_.sPowerAndRegVariables.at(iVar).at(0)),sPolyRegPms_.sPowerAndRegVariables.at(iVar).at(2)) * pow(sRegressionData(i,sPolyRegPms_.sPowerAndRegVariables.at(iVar).at(1)),sPolyRegPms_.sPowerAndRegVariables.at(iVar).at(3)) * dRegCoefs.at(iVar);
            }
        }
        return dPredictedValues;
    }
}