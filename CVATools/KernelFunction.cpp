//
//  KernelFunction.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 20/04/13.
//
//

#include "KernelFunction.h"
#include <stdexcept>
#include <cmath>
#include "Vector.h"

namespace Maths
{
    KernelFunction::KernelFunction(double dh, double dEpsRegression) : dh_(dh), dEpsRegression_(dEpsRegression)
    {}
    
    void KernelFunction::SetBandwidth(double dh)
    {
        dh_ = dh;
    }
    
    double KernelFunction::Estimate(const std::vector<std::pair<double, double> > &dXY, double dX) const
    {
        double dResX = 0., dResXY = 0.;
        for (std::size_t i = 0 ; i < dXY.size() ; ++i)
        {
            dResX += k(fabs(dXY[i].first - dX) / dh_);
            dResXY += k(fabs(dXY[i].first - dX) / dh_) * dXY[i].second;
        }
        if (dResX < dEpsRegression_)
        {
            throw std::runtime_error("Kernel sum too small : cannot compute estimation");
        }
        else
        {
            return dResXY / dResX;
        }
    }
    
    double KernelFunction::Estimate(const std::vector<std::pair<std::vector<double>, double> > & dXY, const std::vector<double> & dX) const
    {
        double dResX = 0., dResXY = 0.;
        for (std::size_t i = 0 ; i < dXY.size() ; ++i)
        {
            dResX += k(Utilities::norm_2(Utilities::Diff(dXY[i].first, dX)) / dh_);
            dResXY += k(Utilities::norm_2(Utilities::Diff(dXY[i].first, dX)) / dh_) * dXY[i].second;
        }
        if (dResX < dEpsRegression_)
        {
            throw std::runtime_error("Kernel sum too small : cannot compute estimation");
        }
        else
        {
            return dResXY / dResX;
        }
    }
}