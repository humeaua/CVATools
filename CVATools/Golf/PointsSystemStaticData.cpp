//
//  PointsSystemStaticData.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 28/12/14.
//
//

#include "PointsSystemStaticData.h"

Utilities::Interp::Interpolator & PointsSystemStaticData::GetOWGRInterpolator()
{
    std::vector<double> variables, values;
    variables.push_back(-0.00001);
    values.push_back(0.0);
    
    variables.push_back(0.0);
    values.push_back(1.0);
    
    variables.push_back(0.25);
    values.push_back(1.0);
    
    variables.push_back(2.0);
    values.push_back(0.0);
    
    variables.push_back(2.00001);
    values.push_back(0.0);
    
    static Utilities::Interp::LinearInterpolator linearInterpolator(variables, values);
    
    return linearInterpolator;
}