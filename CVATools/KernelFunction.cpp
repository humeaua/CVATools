//
//  KernelFunction.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 20/04/13.
//
//

#include "KernelFunction.h"
#include "Require.h"
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
            dResX += k(fabs(dXY.at(i).first - dX) / dh_);
            dResXY += k(fabs(dXY.at(i).first - dX) / dh_) * dXY.at(i).second;
        }
        REQUIREEXCEPTION(fabs(dResX) > dEpsRegression_, "Kernel sum too small - cannot compute estimation");
        
        return dResXY / dResX;
    }
    
    double KernelFunction::Estimate(const std::vector<std::pair<std::vector<double>, double> > & dXY, const std::vector<double> & dX) const
    {
        double dResX = 0., dResXY = 0.;
        for (std::size_t i = 0 ; i < dXY.size() ; ++i)
        {
            dResX += k(Utilities::norm_2(Utilities::Diff(dXY.at(i).first, dX)) / dh_);
            dResXY += k(Utilities::norm_2(Utilities::Diff(dXY.at(i).first, dX)) / dh_) * dXY.at(i).second;
        }
        REQUIREEXCEPTION(fabs(dResX) > dEpsRegression_, "Kernel sum too small : cannot compute estimation");
        
        return dResXY / dResX;
    }
}