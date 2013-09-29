//
//  RegressionData.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 27/07/13.
//
//

#ifndef __CVATools__RegressionData__
#define __CVATools__RegressionData__

#include <vector>

namespace Utilities
{
    class RegressionData
    {
    protected:
        std::vector<double> dData_;
        std::size_t iNObservations_, iNVars_;
    public:
        RegressionData();
        RegressionData(std::size_t iNObservations, std::size_t iNVars);
        RegressionData(const std::vector<double> & dData);
        
        //  Getters
        std::size_t GetNbObservations() const
        {
            return iNObservations_;
        }
        std::size_t GetNbVariables() const
        {
            return iNVars_;
        }
        
        //  Access operators
        double& operator ()(int i, int j);
        double& operator ()(int i, int j) const;
        virtual double& operator ()(size_t i, size_t j);
        virtual double& operator ()(size_t i, size_t j) const;
    };
}

#endif /* defined(__CVATools__RegressionData__) */
