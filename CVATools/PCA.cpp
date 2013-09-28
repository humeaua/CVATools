//
//  PCA.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 28/09/13.
//
//

#include "PCA.h"

namespace Maths
{
    PCA::PCA(const Utilities::Matrix & sCovarianceMatrix) : sEigenVectors_(sCovarianceMatrix.getrows(), sCovarianceMatrix.getcols()), dEigenValues_(sCovarianceMatrix.getrows())
    {
        Utilities::requireException(sCovarianceMatrix.getcols() == sCovarianceMatrix.getrows(), "Covariance must be a square matrix", "PCA::PCA(const Utilities::Matrix & sCovarianceMatrix)");
        
        // Eigen decomposition of the covariance matrix
        int iNRotations = 0;
        Utilities::Eigendecomposition_jacobi(sCovarianceMatrix, sEigenVectors_, dEigenValues_, &iNRotations);
        // sort eigenvalues
        Utilities::eigsrt(dEigenValues_, sEigenVectors_);
        
        std::cout << "PCA succeeded in " << iNRotations << " rotations" << std::endl;
    }
    
    PCA::PCA(const Utilities::RegressionData & sRegressionData) : sEigenVectors_(sRegressionData.GetNbVariables(), sRegressionData.GetNbVariables()), dEigenValues_(sRegressionData.GetNbVariables())
    {
        Utilities::Matrix sCovarianceMatrix(sRegressionData.GetNbVariables(), sRegressionData.GetNbVariables());
        ComputeCovarianceMatrix(sRegressionData, sCovarianceMatrix);
        
        // Eigen decomposition of the covariance matrix
        int iNRotations = 0;
        Utilities::Eigendecomposition_jacobi(sCovarianceMatrix, sEigenVectors_, dEigenValues_, &iNRotations);
        // sort eigenvalues
        Utilities::eigsrt(dEigenValues_, sEigenVectors_);
        
        std::cout << "PCA succeeded in " << iNRotations << " rotations" << std::endl;
    }
    
    PCA::~PCA()
    {
        sEigenVectors_.~Matrix();
        dEigenValues_.clear();
    }
    
    void PCA::ComputeCovarianceMatrix(const Utilities::RegressionData &sRegressionData, Utilities::Matrix &sCovarianceMatrix) const
    {
        sCovarianceMatrix.Reallocate(sRegressionData.GetNbVariables(), sRegressionData.GetNbVariables());
        
        for (std::size_t iVar = 0 ; iVar < sRegressionData.GetNbVariables() ; ++iVar)
        {
            for (std::size_t iPath = 0 ; iPath < sRegressionData.GetNbObservations() ; ++iPath)
            {
                sCovarianceMatrix(iVar, iVar) += sRegressionData(iVar,iPath) * sRegressionData(iVar, iPath);
            }
            sCovarianceMatrix(iVar, iVar) /= sRegressionData.GetNbObservations();
        }
        for (std::size_t iVar = 0 ; iVar < sRegressionData.GetNbVariables() ; ++iVar)
        {
            for (std::size_t jVar = iVar + 1 ; jVar < sRegressionData.GetNbVariables() ; ++jVar)
            {
                for (std::size_t iPath = 0 ; iPath < sRegressionData.GetNbObservations() ; ++iPath)
                {
                    sCovarianceMatrix(iVar, jVar) += sRegressionData(iVar,iPath) * sRegressionData(jVar, iPath);
                }
                sCovarianceMatrix(iVar, jVar) /= sRegressionData.GetNbObservations();
                sCovarianceMatrix(jVar, iVar) = sCovarianceMatrix(iVar, jVar);
            }
        }
    }
}