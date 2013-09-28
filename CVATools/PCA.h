//
//  PCA.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 28/09/13.
//
//

#ifndef __CVATools__PCA__
#define __CVATools__PCA__

#include <iostream>
#include "RegressionData.h"
#include "Matrix.h"
#include "Vector.h"

namespace Maths
{
    class PCA
    {
    private:
        virtual void ComputeCovarianceMatrix(const Utilities::RegressionData & sRegressionData, Utilities::Matrix & sCovarianceMatrix) const;
        
    protected:
        Utilities::Matrix sEigenVectors_;
        Utilities::MyVector<double> dEigenValues_;
        
    public:
        PCA(const Utilities::RegressionData & sRegressionData);
        PCA(const Utilities::Matrix & sCovarianceMatrix);
        virtual ~PCA();
        
    };
}

#endif /* defined(__CVATools__PCA__) */
